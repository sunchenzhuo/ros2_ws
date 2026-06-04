/**
 * @文件路径         : /shu/ros2_ws/src/base_demo_cpp/src/cmd_vel_listener_node.cpp
 * @作者           : 树
 * @创建时间         : 2026-06-03 17:43:25
 * @最后编辑         : 树
 * @最后编辑时间       : 2026-06-04 09:43:41
 * @Version      : V1.0.0
 * @功能描述         :ROS2 底盘速度指令订阅节点。该节点订阅 /cmd_vel 话题，接收 geometry_msgs::msg::Twist 速度控制消息，并将其转换为底盘控制命令字符串 CMD seq vx vy wz。
 * @Copyright    : Copyright (c) 2026 by 树, All Rights Reserved.
 */
#include <functional> // std::bind、std::placeholders::_1
#include <memory>     // std::make_shared
#include <sstream>    // std::ostringstream，用于拼接字符串命令

#include "geometry_msgs/msg/twist.hpp" // ROS2 标准速度消息类型 Twist
#include "rclcpp/rclcpp.hpp"

/**
 * @brief /cmd_vel 速度指令监听节点。
 *
 * CmdVelListenerNode 继承自 rclcpp::Node，表示它是一个 ROS2 节点。
 *
 * 该节点订阅 /cmd_vel 话题，接收 geometry_msgs::msg::Twist 类型消息。
 * Twist 消息通常用于机器人/AGV 底盘速度控制，其中：
 * - linear.x 表示 x 方向线速度 vx；
 * - linear.y 表示 y 方向线速度 vy；
 * - angular.z 表示绕 z 轴角速度 wz。
 *
 * 收到速度指令后，节点会将 ROS2 的 Twist 消息转换为底盘控制命令字符串：
 * CMD seq vx vy wz
 *
 * 后续可以把该命令字符串通过 TCP、串口、CAN 或其他通信方式发送给底盘控制器。
 */
class CmdVelListenerNode : public rclcpp::Node
{
private:
    /**
     * @brief 底盘命令序号。
     *
     * 每收到一次 /cmd_vel 消息，seq_ 自增一次。
     * 用于区分不同的控制命令，也方便后续做请求响应匹配或日志追踪。
     */
    int seq_ = 0;
    /**
     * @brief /cmd_vel 话题订阅者。
     *
     * 用于订阅 geometry_msgs::msg::Twist 类型的速度控制消息。
     *
     * 注意：subscription_ 必须作为成员变量保存。
     * 如果只在构造函数里创建局部变量，构造函数结束后订阅对象会被释放，
     * 节点就无法继续接收 /cmd_vel 消息。
     */
    rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr subscription_;

    /**
     * @brief /cmd_vel 消息回调函数。
     *
     * 当 ROS2 收到 /cmd_vel 话题上的 Twist 消息时，会自动调用该函数。
     *
     * 函数会从 Twist 消息中提取底盘运动控制所需的三个核心字段：
     * - linear.x  -> vx，x 方向线速度；
     * - linear.y  -> vy，y 方向线速度；
     * - angular.z -> wz，z 轴角速度。
     *
     * 然后将其拼接为底盘控制命令字符串：
     * CMD seq vx vy wz
     *
     * @param msg 接收到的 Twist 速度控制消息智能指针。
     */
    void onCmdVel(geometry_msgs::msg::Twist::SharedPtr msg)
    {
        // 从 ROS2 Twist 消息中提取 x 方向线速度
        const double vx = msg->linear.x;

        // 从 ROS2 Twist 消息中提取 y 方向线速度
        const double vy = msg->linear.y;

        // 从 ROS2 Twist 消息中提取 z 轴角速度
        // 对移动机器人/AGV 来说，angular.z 通常表示原地旋转角速度
        const double wz = msg->angular.z;

        // 拼接底盘控制命令字符串。
        //
        // 命令格式：
        // CMD seq vx vy wz
        //
        // 示例：
        // CMD 0 0.30 0.00 0.50
        std::ostringstream cmd;
        cmd << "CMD "
            << seq_ << " "
            << vx << " "
            << vy << " "
            << wz;

        // 打印收到的 ROS2 速度指令，方便调试 /cmd_vel 是否正常接收
        RCLCPP_INFO(this->get_logger(), "receive /cmd_vel: linear x:%.2f linear y:%.2f angular z:%.2f", vx, vy, wz);
        // 打印转换后的底盘控制命令字符串
        RCLCPP_INFO(this->get_logger(), "generate chassis command:%s", cmd.str().c_str());
        seq_++;
    }

public:
    /**
     * @brief CmdVelListenerNode 构造函数。
     *
     * 构造函数中完成节点初始化工作：
     * 1. 设置节点名称为 cmd_vel_listener_node；
     * 2. 创建 /cmd_vel 话题订阅者；
     * 3. 绑定收到消息后的回调函数 onCmdVel；
     * 4. 输出节点启动日志。
     */
    CmdVelListenerNode()
        : Node("cmd_vel_listener_node")
    {
        // 创建 /cmd_vel 订阅者。
        //
        // geometry_msgs::msg::Twist 表示订阅的消息类型是速度控制消息。
        // "/cmd_vel" 是机器人底盘控制中常用的速度指令话题。
        // 10 表示 QoS 队列深度，最多缓存 10 条未处理消息。
        //
        // std::bind(&CmdVelListenerNode::onCmdVel, this, std::placeholders::_1)
        // 表示收到消息后，调用当前对象的 onCmdVel(msg) 成员函数。
        subscription_ = this->create_subscription<geometry_msgs::msg::Twist>(
            "/cmd_vel",
            10,
            std::bind(&CmdVelListenerNode::onCmdVel, this, std::placeholders::_1));
        // 输出节点启动日志
        RCLCPP_INFO(this->get_logger(), "cmd_vel_listener_node started");
    }
};

/**
 * @brief 程序入口函数。
 *
 * main 函数负责初始化 ROS2、创建 CmdVelListenerNode 节点、
 * 启动 ROS2 事件循环，并在程序退出前关闭 ROS2。
 *
 * @param argc 命令行参数数量。
 * @param argv 命令行参数数组。
 * @return int 程序退出码，0 表示正常退出。
 */
int main(int argc, char const *argv[])
{
    // 初始化 ROS2。
    // 所有 ROS2 C++ 程序在创建节点前，都必须先调用 rclcpp::init()。
    rclcpp::init(argc, argv);
    // 创建 /cmd_vel 监听节点。
    // 使用 shared_ptr 管理节点生命周期，这是 ROS2 C++ 常见写法
    auto node = std::make_shared<CmdVelListenerNode>();
    // 启动 ROS2 事件循环。
    //
    // spin 会阻塞当前线程，让节点持续运行。
    // 对订阅者节点来说，只有进入 spin 后，
    // ROS2 才会持续监听 /cmd_vel 话题，并在收到消息时调用 onCmdVel()。
    rclcpp::spin(node);
    // 关闭 ROS2，释放相关资源
    rclcpp::shutdown();
    return 0;
}
