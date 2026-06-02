/**
 * @文件路径         : /shu/ros2_ws/src/base_demo_cpp/src/talker_node.cpp
 * @作者           : 树
 * @创建时间         : 2026-06-02 15:41:22
 * @最后编辑         : 树
 * @最后编辑时间       : 2026-06-02 16:15:56
 * @Version      : V1.0.0
 * @功能描述         :ROS2 C++ 发布者示例节点。该节点创建一个名为 talker_node 的 ROS2 节点，并周期性向 chatter 话题发布 std_msgs::msg::String 字符串消息。
 * @Copyright    : Copyright (c) 2026 by 树, All Rights Reserved.
 */

#include <chrono> // 时间相关库，这里用于 1s 这种时间字面量
#include <memory> // 智能指针库，这里用于 std::make_shared
#include <string> // 字符串库，这里用于 std::string、std::to_string

// ROS2 C++ 客户端库。
// 写 ROS2 C++ 节点基本都会包含这个头文件。
#include "rclcpp/rclcpp.hpp"
// ROS2 标准字符串消息类型。
// std_msgs::msg::String 表示 ROS2 里的字符串消息。
#include "std_msgs/msg/string.hpp"

// 启用 chrono 的时间字面量。
// 使用后可以直接写 1s、500ms 这种时间表达。
using namespace std::chrono_literals;

/**
 * @brief ROS2 字符串发布者节点。
 *
 * TalkerNode 继承自 rclcpp::Node，表示它本身就是一个 ROS2 节点。
 * 该节点内部创建了一个 Publisher，用于向 chatter 话题发布字符串消息；
 * 同时创建了一个 Timer，每隔 1 秒触发一次 onTimer() 回调函数。
 *
 * 节点运行后，会周期性发布：
 * hello ros2 0
 * hello ros2 1
 * hello ros2 2
 * ...
 */
class TalkerNode : public rclcpp::Node
{
private:
    /**
     * @brief 定时器回调函数。
     *
     * 该函数由 ROS2 定时器周期性自动调用。
     * 每次调用时，都会创建一条 std_msgs::msg::String 消息，
     * 将消息内容设置为 hello ros2 + 当前计数值，
     * 然后通过 publisher_ 发布到 chatter 话题。
     */
    void onTimer()
    {
        // 创建一条 ROS2 标准字符串消息。
        // std_msgs::msg::String 是 ROS2 内置的字符串消息类型。
        std_msgs::msg::String msg;

        // 设置消息内容。
        // count_ 是计数器，每发布一次递增一次。
        // 例如 count_=0 时，消息内容为 hello ros20。
        msg.data = "hello ros2 " + std::to_string(count_);

        // 通过发布者将消息发布到 chatter 话题。
        // 只要有订阅者订阅 chatter，就可以收到这条消息。
        publisher_->publish(msg);

        // 打印日志，方便在终端看到当前发布的消息内容。
        // this->get_logger() 获取当前节点的日志器。
        RCLCPP_INFO(this->get_logger(), "publish:%s", msg.data.c_str());

        count_++;
    }
    // 字符串消息发布者。
    // 用于向 chatter 话题发布 std_msgs::msg::String 类型消息。
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;

    // ROS2 定时器对象。
    // 用于周期性触发 onTimer() 回调函数。
    rclcpp::TimerBase::SharedPtr timer_;

    // 消息发布计数器。
    // 每发布一条消息加 1，用于区分不同消息。
    int count_ = 0;

public:
    /**
     * @brief TalkerNode 构造函数。
     *
     * 构造节点时完成三件事：
     * 1. 初始化 ROS2 节点名称为 talker_node；
     * 2. 创建 chatter 话题的字符串消息发布者；
     * 3. 创建 1 秒周期定时器，定时调用 onTimer() 发布消息。
     */
    TalkerNode() : Node("talker_node")
    {
        // 创建一个发布者 Publisher。
        // 模板参数 std_msgs::msg::String 表示发布的消息类型是字符串消息。
        // "chatter" 表示话题名称。
        // 10 表示 QoS 队列深度。
        // 如果发布太快、订阅者处理太慢，最多缓存 10 条消息。
        publisher_ = this->create_publisher<std_msgs::msg::String>("chatter", 10);

        // 创建一个墙上时间定时器。
        // 1s 表示每隔 1 秒触发一次。
        // std::bind(&TalkerNode::onTimer, this) 表示绑定当前对象的 onTimer 成员函数。
        // 定时器启动后，ROS2 执行器 spin 时会自动周期性调用 onTimer()。
        timer_ = this->create_wall_timer(
            1s,
            std::bind(&TalkerNode::onTimer, this));

        // 打印节点启动日志。
        RCLCPP_INFO(this->get_logger(), "talker_node started");
    }
};

/**
 * @brief 程序入口函数。
 *
 * main 函数负责初始化 ROS2、创建节点、启动事件循环，并在退出前关闭 ROS2。
 *
 * @param argc 命令行参数数量。
 * @param argv 命令行参数数组。
 * @return int 程序退出码，0 表示正常退出。
 */
int main(int argc, char const *argv[])
{
    // 初始化 ROS2。
    // 必须先调用 rclcpp::init，后面才能创建 ROS2 节点。
    rclcpp::init(argc, argv);

    // 创建 TalkerNode 节点对象。
    // 使用 shared_ptr 管理节点生命周期，这是 ROS2 C++ 常见写法。
    auto node = std::make_shared<TalkerNode>();

    // 启动 ROS2 事件循环。
    // spin 会阻塞当前线程，让节点持续运行。
    // 定时器回调、订阅回调、服务回调等都需要 spin 才能被执行。
    // 对当前节点来说，spin 后定时器才会每隔 1 秒调用 onTimer()。
    rclcpp::spin(node);

    // 关闭 ROS2。
    // 通常在程序准备退出时调用，用于释放 ROS2 相关资源。
    rclcpp::shutdown();
    return 0;
}
