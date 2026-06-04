/**
 * @文件路径         : /shu/ros2_ws/src/base_demo_cpp/src/base_node.cpp
 * @作者           : 树
 * @创建时间         : 2026-06-04 14:10:58
 * @最后编辑         : 树
 * @最后编辑时间       : 2026-06-04 17:51:21
 * @Version      : V1.0.0
 * @功能描述         :ROS2 底盘模拟节点。该节点订阅 /cmd_vel 速度控制话题，接收底盘运动指令，并周期性发布 /base/status 底盘状态信息。
 * @Copyright    : Copyright (c) 2026 by 树, All Rights Reserved.
 */
#include <chrono>     // 时间库，用于 1000ms 时间字面量
#include <sstream>    // std::ostringstream，用于拼接状态字符串
#include <iomanip>    // std::fixed、std::setprecision，用于格式化小数
#include <string>     // std::string 字符串类型
#include <memory>     // std::make_shared，用于创建智能指针
#include <functional> // std::bind、std::placeholders
#include <mutex>

#include "rclcpp/rclcpp.hpp"           // ROS2 C++ 客户端库
#include "geometry_msgs/msg/twist.hpp" // Twist 速度控制消息类型
#include "std_msgs/msg/string.hpp"     // String 字符串消息类型

// 启用 chrono 时间字面量。
// 使用后可以直接写 1000ms、1s 这种时间表达
using namespace std::chrono_literals;
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
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr status_pub_;
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

    int seq_ = 0;
    double vx_ = 0.0;
    double vy_ = 0.0;
    double wz_ = 0.0;
    std::mutex cmd_mutex_;

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
        std::lock_guard<std::mutex> lock(cmd_mutex_);
        vx_ = msgs->linear.x;
        vy_ = msgs->linear.y;
        wz_ = msgs->angular.z;

        RCLCPP_INFO(this->get_logger(),
                    "receive /cmd_vel vx=%.2f vy=%.2f wz=%.2f", vx_, vy_, wz_);
    }

    /**
     * @brief 定时器回调函数。
     *
     * 该函数由 ROS2 定时器周期性调用，用于发布底盘状态。
     *
     * 每次触发时，会完成以下流程：
     * 1. 从成员变量中读取当前 vx、vy、wz；
     * 2. 模拟生成电池电压 battery_voltage；
     * 3. 根据电池电压判断错误状态 err；
     * 4. 拼接状态字符串；
     * 5. 发布到 /base/status 话题；
     * 6. 状态序号 seq_ 自增。
     *
     * 注意：
     * 为了避免长时间持锁，本函数只在锁内复制 vx_、vy_、wz_，
     * 后续字符串拼接、日志输出、消息发布都在锁外执行。
     */
    void onTimer()
    {
        // 局部变量，用于保存当前速度快照。
        // 这样后续拼接日志和发布消息时，不需要一直持有锁。
        double current_vx = 0.0;
        double current_vy = 0.0;
        double current_wz = 0.0;

        {
            // 加锁读取共享速度数据。
            std::lock_guard<std::mutex> lock(cmd_mutex_);
            // // 复制当前速度状态到局部变量。
            current_vx = vx_;
            current_vy = vy_;
            current_wz = wz_;
        }
        double battery_voltage = 12.6 - 0.01 * seq_;
        std::string err = "OK";

        if (battery_voltage < 10.5)
        {
            battery_voltage = 10.5;
            err = "LOW_BATTERY";
        }

        std_msgs::msg::String msg;
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2) << " seq=" << seq_ << " vx=" << current_vx << " vy=" << current_vy << " wz=" << current_wz << " battery_voltage=" << battery_voltage << " err=" << err;
        msg.data = oss.str();
        status_pub_->publish(msg);

        RCLCPP_INFO(this->get_logger(), "publish /base/status: %s", msg.data.c_str());
        seq_++;
    }

public:
    /**
     * @brief BaseNode 构造函数。
     *
     * 构造函数负责初始化底盘节点，包括：
     * 1. 设置节点名称为 base_node；
     * 2. 创建 /base/status 状态发布者；
     * 3. 创建 /cmd_vel 速度指令订阅者；
     * 4. 创建周期定时器，定时发布底盘状态；
     * 5. 输出节点启动日志。
     */
    BaseNode() : Node("base_node")
    {
        // 创建底盘状态发布者。
        //
        // 话题名：/base/status
        // 消息类型：std_msgs::msg::String
        // QoS 队列深度：10
        status_pub_ = this->create_publisher<std_msgs::msg::String>("/base/status", 10);

        // 创建速度控制指令订阅者。
        //
        // 话题名：/cmd_vel
        // 消息类型：geometry_msgs::msg::Twist
        // QoS 队列深度：10
        //
        // 注意：std::bind 绑定成员函数时，必须传入 this。
        // 正确写法：
        // std::bind(&BaseNode::onCmdVel, this, std::placeholders::_1)
        cmd_vel_sub_ = this->create_subscription<geometry_msgs::msg::Twist>(
            "cmd_vel",
            10,
            std::bind(&BaseNode::onCmdVel, this, std::placeholders::_1));

        // 创建定时器。
        //
        // 1000ms 表示每 1000 毫秒触发一次，也就是每 1 秒调用一次 onTimer()。
        timer_ = this->create_wall_timer(1000ms, std::bind(&BaseNode::onTimer, this));

        RCLCPP_INFO(this->get_logger(), "base_node started");
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