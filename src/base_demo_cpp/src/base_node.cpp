/**
 * @文件路径         : /shu/ros2_ws/src/base_demo_cpp/src/base_node.cpp
 * @作者           : 树
 * @创建时间         : 2026-06-04 14:10:58
 * @最后编辑         : 树
 * @最后编辑时间       : 2026-06-08 15:48:52
 * @Version      : V1.0.0
 * @功能描述         :ROS2 底盘模拟节点。该节点订阅 /cmd_vel 速度控制话题，接收底盘运动指令，并周期性发布 /base/status 底盘状态信息。
 * @Copyright    : Copyright (c) 2026 by 树, All Rights Reserved.
 */
#include <chrono>     // 时间库，用于 1000ms 时间字面量
#include <string>     // std::string 字符串类型
#include <memory>     // std::make_shared，用于创建智能指针
#include <functional> // std::bind、std::placeholders
#include <mutex>
#include <vector>
#include <sstream>
#include <iomanip>

#include "rclcpp/rclcpp.hpp"                 // ROS2 C++ 客户端库
#include "geometry_msgs/msg/twist.hpp"       // Twist 速度控制消息类型
#include "base_demo_cpp/msg/base_status.hpp" // 自定义 BaseStatus 消息类型
#include "rcl_interfaces/msg/set_parameters_result.hpp"
#include "base_demo_cpp/tcp_client.hpp"

// 启用 chrono 时间字面量。
// 使用后可以直接写 1000ms、1s 这种时间表达
using namespace std::chrono_literals;

struct ChassisStatus
{
  int seq = 0;
  double vx = 0.00;
  double vy = 0.00;
  double wz = 0.00;
  double battery_voltage = 0.00;
  int err_code = -1;
};
/**
 * @brief 底盘模拟节点。
 *
 * BaseNode 继承自 rclcpp::Node，表示它是一个 ROS2 节点。
 *
 * 该节点模拟一个简化版 AGV/机器人底盘模块，主要完成两个功能：
 *
 * 1. 订阅 /cmd_vel 话题：
 *    接收 geometry_msgs::msg::Twist 类型速度控制指令，
 *    并提取 linear.x、linear.y、angular.z 作为底盘速度 vx、vy、wz。
 *
 * 2. 发布 /base/status 话题：
 *    周期性发布当前底盘状态，包括 seq、vx、vy、wz、电池电压和错误状态。
 *
 * 由于本节点使用 MultiThreadedExecutor 运行，订阅回调和定时器回调
 * 可能在不同线程中并发执行，因此访问 vx_、vy_、wz_ 时需要使用 mutex 保护。
 */
class BaseNode : public rclcpp::Node
{
private:
  /**
   * @brief 底盘状态发布者。
   *
   * 用于向 /base/status 话题发布 std_msgs::msg::String 类型状态消息。
   */
  rclcpp::Publisher<base_demo_cpp::msg::BaseStatus>::SharedPtr status_pub_;
  /**
   * @brief 速度控制指令订阅者。
   *
   * 用于订阅 /cmd_vel 话题，接收 geometry_msgs::msg::Twist 类型速度消息。
   */
  rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr cmd_vel_sub_;
  /**
   * @brief 定时器对象。
   *
   * 用于周期性触发 onTimer()，实现定时发布底盘状态。
   */
  rclcpp::TimerBase::SharedPtr timer_;

  /**
   * @brief /cmd_vel 订阅回调组。
   *
   * callback group 用于控制回调函数的调度方式。
   * 这里将 /cmd_vel 订阅回调单独放到一个回调组中。
   */
  rclcpp::CallbackGroup::SharedPtr cmd_group_;
  /**
   * @brief 定时器回调组。
   *
   * 定时器回调 onTimer() 使用独立回调组。
   * 在 MultiThreadedExecutor 下，不同回调组中的回调可能被不同线程调度。
   */
  rclcpp::CallbackGroup::SharedPtr timer_group_;
  /**
   * @brief 最近一次收到 /cmd_vel 指令的时间。
   *
   * 用于判断速度控制指令是否超时。
   */
  rclcpp::Time last_cmd_time_;

  rclcpp::node_interfaces::OnSetParametersCallbackHandle::SharedPtr param_call_handle_;

  int seq_ = 0;
  double vx_ = 0.0;
  double vy_ = 0.0;
  double wz_ = 0.0;
  int cmd_timeout_ms_ = 1000;
  std::mutex cmd_mutex_;
  bool cmd_timeout_active_ = false;
  std::string server_ip_ = "127.0.0.1";
  int server_port_ = 17000;

  std::string errorCodeToString(int err_code)
  {
    if (err_code == 0)
    {
      return "OK";
    }
    if (err_code == 1)
    {
      return "LOW_BATTERY_VOLTAGE";
    }
    return "UNKNOW";
  }

private:
  /**
   * @brief /cmd_vel 速度指令回调函数。
   *
   * 当节点收到 /cmd_vel 话题上的 Twist 消息时，ROS2 会自动调用该函数。
   *
   * 函数会从 Twist 消息中提取：
   * - linear.x 作为 vx；
   * - linear.y 作为 vy；
   * - angular.z 作为 wz。
   *
   * 提取后的速度会保存到成员变量 vx_、vy_、wz_ 中，
   * 后续 onTimer() 发布底盘状态时会使用这些最新速度值。
   *
   * @param msg 接收到的 Twist 速度控制消息智能指针。
   */
  void onCmdVel(const geometry_msgs::msg::Twist::SharedPtr msgs)
  {
    {
      // 加锁更新共享速度和时间状态。
      std::lock_guard<std::mutex>
          lock(cmd_mutex_);
      vx_ = msgs->linear.x;
      vy_ = msgs->linear.y;
      wz_ = msgs->angular.z;
      // 记录最近一次收到 /cmd_vel 的时间。
      last_cmd_time_ = this->now();
      // 收到新指令后，清除超时状态。
      cmd_timeout_active_ = false;
    }

    RCLCPP_INFO(this->get_logger(),
                "receive /cmd_vel vx=%.2f vy=%.2f wz=%.2f",
                msgs->linear.x,
                msgs->linear.y,
                msgs->angular.z);
  }

  /**
   * @brief 定时器回调函数。
   *
   * 该函数由 ROS2 定时器周期性调用，用于发布底盘状态。
   *
   * 每次触发时，会完成以下流程：
   * 1. 判断 /cmd_vel 是否超时；
   * 2. 如果未超时，读取当前 vx、vy、wz；
   * 3. 如果已超时，将 vx、vy、wz 置为 0；
   * 4. 模拟生成电池电压 battery_voltage；
   * 5. 拼接状态字符串；
   * 6. 发布到 /base/status 话题。
   */
  void onTimer()
  {
    // 局部变量，用于保存当前速度快照。
    // 这样后续拼接日志和发布消息时，不需要一直持有锁。
    double current_vx = 0.0;
    double current_vy = 0.0;
    double current_wz = 0.0;
    int current_cmd_timeout_ms = 1000;

    // 标记当前这次定时器检查时，/cmd_vel 是否已经超时。
    // true  表示超过 cmd_timeout_ms_ 时间没有收到新的速度指令；
    // false 表示 /cmd_vel 指令仍然有效。
    bool cmd_timeout = false;
    // 标记本轮是否需要打印超时告警。
    // 这个变量用于控制“只在刚进入超时状态时打印一次告警”，避免每秒重复刷日志。
    bool should_warn_timeout = false;

    // 保存最近一次收到 /cmd_vel 指令的时间快照。
    // 注意：这里使用局部变量，是为了在锁内快速复制共享数据，锁外再做耗时判断。
    rclcpp::Time last_cmd_time;
    // 保存当前是否已经处于超时状态的快照。
    // cmd_timeout_active_ 是共享变量，需要加锁读取；
    // timeout_active 是它的本地副本，后续锁外判断使用。
    bool timeout_active = false;

    {
      // 加锁读取共享状态。
      //
      // vx_、vy_、wz_、last_cmd_time_、cmd_timeout_active_
      // 可能会被 onCmdVel() 回调更新。
      //
      // 当前 onTimer() 也要读取这些数据，因此必须加锁，
      // 避免多线程读写导致数据竞争。
      std::lock_guard<std::mutex> lock(cmd_mutex_);

      // 复制当前速度到局部变量。
      // 这样锁释放后，后续拼接状态、发布消息时都使用局部变量，
      // 不需要长时间持有 mutex。
      current_vx = vx_;
      current_vy = vy_;
      current_wz = wz_;

      // 复制最近一次收到 /cmd_vel 的时间。
      last_cmd_time = last_cmd_time_;
      // 复制当前是否已经处于超时状态。
      timeout_active = cmd_timeout_active_;

      current_cmd_timeout_ms = cmd_timeout_ms_;
    }

    // 获取当前 ROS2 时间。
    const auto now = this->now();
    // 计算距离上一次收到 /cmd_vel 已经过去了多少毫秒。
    // now - last_cmd_time 得到时间差，单位是纳秒；
    // 除以 1000000 后转换成毫秒。
    const long elapsed_ms = static_cast<long>((now - last_cmd_time).nanoseconds() / 1000000);

    // 判断 /cmd_vel 是否超时。
    // 如果距离上一次收到控制指令的时间超过 cmd_timeout_ms_，则认为控制指令超时。
    cmd_timeout = elapsed_ms > current_cmd_timeout_ms;

    if (cmd_timeout)
    {
      // 控制指令超时后，将速度置 0。
      //
      // 这模拟真实底盘里的安全停车逻辑：
      // 如果长时间收不到上层控制指令，不能继续沿用旧速度运行，
      // 否则机器人/AGV 可能一直运动，存在安全风险。
      current_vx = 0.0;
      current_vy = 0.0;
      current_wz = 0.0;

      // 只在刚进入超时状态时打印一次告警。
      //
      // timeout_active 是刚才从 cmd_timeout_active_ 复制出来的快照。
      // 如果它是 false，说明之前还没有进入超时状态；
      // 本轮第一次发现超时，就需要打印告警。
      if (!timeout_active)
      {
        // 标记本轮需要打印超时告警。
        should_warn_timeout = true;

        // 更新共享超时状态。
        //
        // cmd_timeout_active_ 是成员变量，可能被 onCmdVel() 修改，
        // 所以写它时也要加锁。
        std::lock_guard<std::mutex> lock(cmd_mutex_);
        cmd_timeout_active_ = true;
      }
    }

    // 如果本轮是“刚进入超时状态”，则打印一次告警日志。
    if (should_warn_timeout)
    {
      RCLCPP_WARN(this->get_logger(),
                  "cmd_vel timeout, stop chassis, elapsed_ms=%ld, timeout_ms=%d",
                  elapsed_ms,
                  current_cmd_timeout_ms);
    }

    // 模拟电池电压。
    double battery_voltage = 12.6 - 0.01 * seq_;
    std::string err = "OK";

    if (battery_voltage < 10.5)
    {
      battery_voltage = 10.5;
      err = "LOW_BATTERY";
    }

    // 使用字符串输出流拼接待发送的底盘控制命令
    // std::fixed + std::setprecision(2) 表示浮点数固定保留 2 位小数
    std::ostringstream cmd_oss;
    cmd_oss << std::fixed << std::setprecision(2);

    // 组装 CMD 控制报文
    // 报文格式：CMD seq vx vy wz
    // 示例：CMD 1 0.10 0.00 0.20
    cmd_oss << "CMD " << seq_
            << " " << current_vx
            << " " << current_vy
            << " " << current_wz;

    // 将拼接完成的命令转换为字符串，准备通过 TCP 发送
    std::string cmd = cmd_oss.str();

    // 创建 TCP 客户端对象，用于连接 QEMU 仿真端
    TcpClient client;
    // 连接 QEMU 服务端，如果连接失败则打印错误日志
    if (!client.connectTo(server_ip_, server_port_))
    {
      RCLCPP_ERROR(
          this->get_logger(),
          "connect qemu failed : %s:%d",
          server_ip_.c_str(),
          server_port_);
    }
    else
    {
      // 连接成功后，打印即将发送的 CMD 控制命令
      RCLCPP_INFO(
          this->get_logger(),
          "TX:%s",
          cmd.c_str());
      // 通过 TCP 向 QEMU 发送一行 CMD 控制命令
      if (!client.sendLine(cmd))
      {
        RCLCPP_ERROR(
            this->get_logger(),
            "send CMD failed");
      }
      else
      {
        // CMD 发送成功后，等待接收 QEMU 返回的 STA 状态报文
        std::string reply;
        if (!client.receiveLine(reply))
        {
          RCLCPP_ERROR(
              this->get_logger(),
              "receive STA failed");
        }
        else
        {
          // 成功接收到 STA 状态报文，打印原始返回内容
          RCLCPP_INFO(
              this->get_logger(),
              "RX:%s",
              reply.c_str());

          // 定义底盘状态结构体，用于保存解析后的状态数据
          ChassisStatus chassis_status;

          // 解析 STA 状态报文
          // 预期格式：STA seq vx vy wz battery_voltage err_code
          if (parseSta(reply, chassis_status))
          {
            // 解析成功后，打印底盘状态信息
            RCLCPP_INFO(
                this->get_logger(),
                "parsed STA seq=%d, vx=%.2f, vy=%.2f, wz=%.2f battery_voltage=%.2f, err_code=%d",
                chassis_status.seq,
                chassis_status.vx,
                chassis_status.vy,
                chassis_status.wz,
                chassis_status.battery_voltage,
                chassis_status.err_code);
          }
          else
          {
            // 解析失败时，打印原始 STA 报文，方便排查协议格式问题
            RCLCPP_ERROR(
                this->get_logger(),
                "parsed STA failed: %s",
                reply.c_str());
          }
        }
      }
    }

    // 创建结构化底盘状态消息。
    base_demo_cpp::msg::BaseStatus msg;

    msg.seq = seq_;
    msg.vx = current_vx;
    msg.vy = current_vy;
    msg.wz = current_wz;
    msg.battery_voltage = battery_voltage;
    msg.err = err;
    msg.cmd_timeout = cmd_timeout;

    status_pub_->publish(msg);

    RCLCPP_INFO(
        this->get_logger(),
        "publish /base/status: seq=%d vx=%.2f vy=%.2f wz=%.2f battery_voltage=%.2f err=%s cmd_timeout=%d",
        msg.seq,
        msg.vx,
        msg.vy,
        msg.wz,
        msg.battery_voltage,
        msg.err.c_str(),
        msg.cmd_timeout ? 1 : 0);

    seq_++;
  }

  /**
   * @brief ROS2 参数动态修改回调函数
   *
   * 当节点运行过程中通过 ros2 param set 修改参数时，
   * ROS2 会自动调用该回调函数。
   *
   * 当前函数主要处理 cmd_timeout_ms 参数：
   * - 用于控制 /cmd_vel 指令的超时时间
   * - 如果超过该时间没有收到新的速度指令，则底盘进入安全停车逻辑
   *
   * @param parameters 本次被修改的参数列表
   * @return rcl_interfaces::msg::SetParametersResult
   *         返回参数修改是否成功，以及失败原因
   */
  rcl_interfaces::msg::SetParametersResult onParamterChanger(const std::vector<rclcpp::Parameter> &parameters)
  {
    // 创建参数修改结果对象。
    // ROS2 要求参数回调必须返回 SetParametersResult，
    // 用于告诉系统本次参数修改是否允许生效。
    rcl_interfaces::msg::SetParametersResult result;
    // 默认认为本次参数修改成功。
    // 如果后续检查发现参数非法，再将 successful 改为 false。
    result.successful = true;

    // 遍历本次修改的所有参数。
    // 一次 ros2 param set 通常只修改一个参数，
    // 但 ROS2 接口支持一次传入多个参数，所以这里使用循环处理。
    for (const auto &param : parameters)
    {
      // 判断当前参数是否是底盘控制指令超时时间参数。
      //
      // cmd_timeout_ms 表示：
      // 如果超过该毫秒数没有收到新的 /cmd_vel 指令，
      // 则认为上层控制指令超时，底盘应停止运动。
      if (param.get_name() == "cmd_timeout_ms")
      {
        // 将参数值读取为 int 类型。
        // 注意：这里要求 cmd_timeout_ms 在声明参数时就是整数类型，
        // 否则 as_int() 可能会触发异常。
        int new_timeout = param.as_int();

        // 参数合法性校验。
        //
        // 超时时间必须大于 0。
        // 如果设置成 0 或负数，超时判断逻辑会失去意义，
        // 甚至可能导致底盘控制行为异常。
        if (new_timeout <= 0)
        {
          // 标记本次参数修改失败。
          result.successful = false;

          // 返回失败原因。
          // 用户执行 ros2 param set 时，可以看到该错误信息。
          result.reason = "cmd_timeout_ms must be > 0";

          // 直接返回，不允许该非法参数生效。
          return result;
        }
        {
          // 加锁保护共享状态。
          //
          // cmd_timeout_ms_、cmd_timeout_active_、last_cmd_time_
          // 可能会被 onTimer() 或 onCmdVel() 等回调同时访问。
          //
          // 因此修改这些成员变量时必须加锁，
          // 避免多线程并发读写导致数据竞争。
          std::lock_guard<std::mutex> lock(cmd_mutex_);

          // 更新底盘控制指令超时时间。
          cmd_timeout_ms_ = new_timeout;

          // 重置超时状态。
          //
          // 因为超时时间刚刚被重新设置，
          // 这里将 cmd_timeout_active_ 置为 false，
          // 表示当前不再认为底盘处于超时状态。
          cmd_timeout_active_ = false;

          // 重置最近一次指令时间。
          //
          // 这样做可以避免刚修改完参数后，
          // onTimer() 立刻使用旧的 last_cmd_time_ 判断为超时。
          //
          // 相当于告诉系统：
          // 从当前时间开始重新计算 /cmd_vel 超时时间。
          last_cmd_time_ = this->now();
        }
        // 打印参数修改成功日志，便于运行时排查。
        RCLCPP_INFO(this->get_logger(),
                    "cmd_timeout_ms changed to %d",
                    new_timeout);
      }
    }
    return result;
  }

  bool parseSta(const std::string &line, ChassisStatus &status)
  {
    std::istringstream iss(line);

    std::string tag;
    iss >> tag;
    if (tag != "STA")
    {
      return false;
    }

    iss >> status.seq >> status.vx >> status.vy >> status.wz >> status.battery_voltage >> status.err_code;
    return !iss.fail();
  }

public:
  /**
   * @brief BaseNode 构造函数。
   *
   * 构造函数负责初始化底盘节点，包括：
   * 1. 设置节点名称为 base_node；
   * 2. 创建 callback group；
   * 3. 创建 /base/status 状态发布者；
   * 4. 创建 /cmd_vel 速度指令订阅者；
   * 5. 创建周期定时器；
   * 6. 输出节点启动日志。
   */
  BaseNode() : Node("base_node")
  {
    // 声明参数：/cmd_vel 超时时间，默认 1000ms。
    this->declare_parameter<int>("cmd_timeout_ms", 1000);
    this->declare_parameter<std::string>("server_ip", "127.0.0.1");
    this->declare_parameter<int>("server_port", 17000);
    cmd_timeout_ms_ = this->get_parameter("cmd_timeout_ms").as_int();
    param_call_handle_ = this->add_on_set_parameters_callback(
        std::bind(
            &BaseNode::onParamterChanger,
            this,
            std::placeholders::_1));

    // 初始化最近一次控制指令时间。
    // 节点刚启动时还没有收到 /cmd_vel，这里先用当前时间初始化。
    cmd_timeout_active_ = false;
    last_cmd_time_ = this->now();

    // 先创建回调组。
    //
    // 注意：
    // callback group 必须先创建，再传给订阅者和定时器。
    // 如果先把空的 cmd_group_ / timer_group_ 传进去，再创建它们，
    // 订阅者和定时器并不会自动绑定到后面新创建的回调组上。
    cmd_group_ = this->create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);
    timer_group_ = this->create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);

    // 创建底盘状态发布者。
    status_pub_ = this->create_publisher<base_demo_cpp::msg::BaseStatus>("/base/status", 10);
    server_ip_ = this->get_parameter("server_ip").as_string();
    server_port_ = this->get_parameter("server_port").as_int();

    RCLCPP_INFO(
        this->get_logger(),
        "qemu server_ip=%s server_port=%d",
        server_ip_.c_str(),
        server_port_);

    // 创建订阅选项，并指定 /cmd_vel 订阅者使用 cmd_group_ 回调组。
    rclcpp::SubscriptionOptions cmd_options;
    cmd_options.callback_group = cmd_group_;
    // 创建速度控制指令订阅者。
    //
    // 话题名：/cmd_vel
    // 消息类型：geometry_msgs::msg::Twist
    // QoS 队列深度：10
    //
    // 注意：
    // 这里建议写成绝对话题名 "/cmd_vel"，避免命名空间影响。
    cmd_vel_sub_ = this->create_subscription<geometry_msgs::msg::Twist>(
        "/cmd_vel",
        10,
        std::bind(&BaseNode::onCmdVel, this, std::placeholders::_1),
        cmd_options);

    // 创建定时器。
    //
    // 1000ms 表示每 1000 毫秒触发一次，也就是每 1 秒调用一次 onTimer()。
    //
    // 第三个参数 timer_group_ 表示该定时器回调属于 timer_group_。
    timer_ = this->create_wall_timer(1000ms,
                                     std::bind(&BaseNode::onTimer, this),
                                     timer_group_);

    RCLCPP_INFO(this->get_logger(), "base_node started");
    RCLCPP_INFO(this->get_logger(), "cmd_timeout_ms=%d", cmd_timeout_ms_);
  }
};

/**
 * @brief 程序入口函数。
 *
 * main 函数负责初始化 ROS2、创建 BaseNode 节点、
 * 使用多线程执行器运行节点，并在程序退出前关闭 ROS2。
 *
 * @param argc 命令行参数数量。
 * @param argv 命令行参数数组。
 * @return int 程序退出码，0 表示正常退出。
 */
int main(int argc, char const *argv[])
{
  // 初始化 ROS2。
  // 所有 ROS2 C++ 程序在创建节点之前，都需要先调用 rclcpp::init()。
  rclcpp::init(argc, argv);
  // 创建多线程执行器。
  //
  // MultiThreadedExecutor 可以使用多个线程处理回调。
  // 例如订阅回调 onCmdVel() 和定时器回调 onTimer()
  // 可能被不同线程并发执行。
  //
  // 因为本程序使用多线程执行器，所以共享数据 vx_、vy_、wz_
  // 需要使用 mutex 保护。
  rclcpp::executors::MultiThreadedExecutor executor;
  // 创建 BaseNode 节点对象。
  // 使用 shared_ptr 管理节点生命周期，这是 ROS2 C++ 常见写法。
  auto node = std::make_shared<BaseNode>();

  // 将节点添加到执行器中。
  // 添加后，executor 才能调度该节点的订阅回调和定时器回调。
  executor.add_node(node);

  // 启动执行器事件循环。
  //
  // spin() 会阻塞当前线程，使节点持续运行。
  // 在运行期间，执行器会负责调度：
  // - /cmd_vel 订阅回调 onCmdVel()
  // - 定时器回调 onTimer()
  executor.spin();
  // 关闭 ROS2，释放相关资源。
  rclcpp::shutdown();
  return 0;
}