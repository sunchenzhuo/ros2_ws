/**
 * @文件路径         : /shu/ros2_ws/src/base_demo_cpp/src/listener_node.cpp
 * @作者           : 树
 * @创建时间         : 2026-06-02 16:23:38
 * @最后编辑         : 树
 * @最后编辑时间       : 2026-06-02 17:14:40
 * @Version      : V1.0.0
 * @功能描述         :ROS2 C++ 订阅者示例节点。该节点创建一个名为 listener_node 的 ROS2 节点，订阅 chatter 话题，并在收到 std_msgs::msg::String 字符串消息后输出接收日志。
 * @Copyright    : Copyright (c) 2026 by 树, All Rights Reserved.
 */
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

/**
 * @brief ROS2 字符串订阅者节点。
 *
 * ListenerNode 继承自 rclcpp::Node，表示它是一个 ROS2 节点。
 * 该节点会订阅 chatter 话题，接收 std_msgs::msg::String 类型的字符串消息。
 *
 * 当 talker_node 向 chatter 话题发布消息时，
 * listener_node 会自动触发 onMessage() 回调函数，并打印接收到的内容。
 */
class ListenerNode : public rclcpp::Node
{
public:
    /**
     * @brief ListenerNode 构造函数。
     *
     * 构造函数中完成两件事：
     * 1. 初始化 ROS2 节点名称为 listener_node；
     * 2. 创建 chatter 话题的订阅者 subscription_。
     */
    ListenerNode()
        : Node("listener_node") // 初始化父类 rclcpp::Node，并设置节点名称
    {
        // 创建订阅者。
        // 模板参数 std_msgs::msg::String 表示订阅的消息类型是字符串消息。
        // "chatter" 表示订阅的话题名称。
        // 10 表示 QoS 队列深度，最多缓存 10 条未处理消息。
        // std::bind(&ListenerNode::onMessage, this, std::placeholders::_1)
        // 表示当收到消息时，调用当前对象的 onMessage() 成员函数。
        // std::placeholders::_1 表示回调函数的第一个参数，
        // 也就是收到的消息对象 msg。
        subscription_ = this->create_subscription<std_msgs::msg::String>(
            "chatter",
            10,
            std::bind(&ListenerNode::onMessage, this, std::placeholders::_1));

        // 输出节点启动日志。
        RCLCPP_INFO(this->get_logger(), "listener_node started");
    }

private:
    /**
     * @brief 话题消息回调函数。
     *
     * 当 listener_node 从 chatter 话题收到一条字符串消息时，
     * ROS2 会自动调用该函数。
     *
     * @param msg 接收到的字符串消息智能指针。
     */
    void onMessage(const std_msgs::msg::String::SharedPtr msg)
    {
        // 打印接收到的消息内容。
        // msg->data 是 std_msgs::msg::String 消息中的字符串字段。
        // c_str() 用于把 std::string 转成 C 风格字符串，
        // 以便 RCLCPP_INFO 使用 %s 格式化输出。
        RCLCPP_INFO(this->get_logger(), "receive: '%s'", msg->data.c_str());
    }
    // 字符串消息订阅者。
    // 用于订阅 chatter 话题上的 std_msgs::msg::String 消息。
    // 必须作为成员变量保存，否则构造函数结束后订阅者对象被释放，
    // 节点就无法继续接收消息。
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
};

/**
 * @brief 程序入口函数。
 *
 * main 函数负责初始化 ROS2、创建 listener_node 节点、
 * 启动 ROS2 事件循环，并在程序退出前关闭 ROS2。
 *
 * @param argc 命令行参数数量。
 * @param argv 命令行参数数组。
 * @return int 程序退出码，0 表示正常退出。
 */
int main(int argc, char *argv[])
{
    // 初始化 ROS2。
    // 所有 ROS2 C++ 程序在创建节点之前，都需要先调用 rclcpp::init()。
    rclcpp::init(argc, argv);

    // 创建 ListenerNode 节点对象。
    // 使用 shared_ptr 管理节点生命周期，这是 ROS2 C++ 的常见写法。
    auto node = std::make_shared<ListenerNode>();

    // 启动 ROS2 事件循环。
    //
    // spin 会阻塞当前线程，让节点持续运行。
    // 对订阅者节点来说，只有进入 spin 后，
    // ROS2 才会持续监听 chatter 话题，并在收到消息时调用 onMessage()。
    rclcpp::spin(node);

    // 关闭 ROS2，释放相关资源。
    rclcpp::shutdown();

    return 0;
}