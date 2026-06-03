/**
 * @文件路径         : /shu/ros2_ws/src/base_demo_cpp/src/base_status_node.cpp
 * @作者           : 树
 * @创建时间         : 2026-06-03 14:26:51
 * @最后编辑         : 树
 * @最后编辑时间       : 2026-06-03 17:21:39
 * @Version      : V1.0.0
 * @功能描述         :ROS2 底盘状态模拟发布节点。该节点周期性生成底盘速度、电池电压和错误状态信息，并以字符串消息形式发布到 base_status 话题。
 * @Copyright    : Copyright (c) 2026 by 树, All Rights Reserved.
 */

#include <chrono>  // 时间相关库，用于 1s 时间字面量
#include <iomanip> // 格式化输出库，用于 std::fixed、std::setprecision
#include <memory>  // 智能指针库，用于 std::make_shared
#include <sstream> // 字符串流库，用于拼接状态字符串
#include <string>  // 字符串库，用于 std::string

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

// 启用 chrono 时间字面量
// 使用后可以直接写 1s、500ms 等时间表达
using namespace std::chrono_literals;

/**
 * @brief 底盘状态模拟发布节点。
 *
 * BaseStatusNode 继承自 rclcpp::Node，表示它是一个 ROS2 节点。
 *
 * 该节点会周期性模拟底盘状态数据，包括：
 * 1. seq：状态序号；
 * 2. vx：x 方向线速度；
 * 3. vy：y 方向线速度；
 * 4. wz：z 轴角速度；
 * 5. battery_voltage：电池电压；
 * 6. err：错误状态。
 *
 * 节点每隔 1 秒将状态数据拼接成字符串，并发布到 base_status 话题。
 */
class BaseStatusNode : public rclcpp::Node
{
    /**
     * @brief 状态发布计数器。
     *
     * 每发布一次状态消息，count_ 自增一次。
     * 该字段既用于生成 seq 序号，也用于模拟电池电压逐渐下降。
     */
    int count_ = 0;
    /**
     * @brief 底盘状态消息发布者。
     *
     * 用于向 base_status 话题发布 std_msgs::msg::String 类型消息。
     */
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    /**
     * @brief ROS2 定时器对象。
     *
     * 用于周期性触发 onTimer() 回调函数，实现定时发布底盘状态。
     */
    rclcpp::TimerBase::SharedPtr timer_;

private:
    /**
     * @brief 定时器回调函数。
     *
     * 该函数由 ROS2 定时器周期性调用。
     *
     * 每次触发时，函数会模拟生成一组底盘状态数据：
     * - 固定 vx、vy、wz；
     * - 根据 count_ 模拟电池电压逐渐下降；
     * - 当电池电压低于阈值时，将错误状态设置为 LOW_BATTERY；
     * - 最后将状态数据拼接成字符串并发布到 base_status 话题。
     */
    void onTimer()
    {
        const double vx = 0.30;
        const double vy = 0.00;
        const double wz = 0.50;

        double battery_voltage = 12.60 - 0.01 * count_;
        if (battery_voltage < 9.00)
        {
            battery_voltage = 9.00;
        }
        std::string err = "OK";
        if (battery_voltage < 10.60)
        {
            err = "LOW_BATTERY";
        }

        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2)
            << "seq=" << count_
            << " vx=" << vx
            << " vy=" << vy
            << " wz=" << wz
            << " battery_voltage=" << battery_voltage
            << " err=" << err;

        std_msgs::msg::String msg;
        msg.data = oss.str();
        publisher_->publish(msg);

        RCLCPP_INFO(this->get_logger(), "public /base/status :'%s'", msg.data.c_str());

        count_++;
    }

    /**
     * @brief BaseStatusNode 构造函数。
     *
     * 构造函数中完成节点初始化工作：
     * 1. 设置节点名称为 base_status_node；
     * 2. 创建 base_status 话题发布者；
     * 3. 创建 1 秒周期定时器；
     * 4. 输出节点启动日志。
     */
public:
    BaseStatusNode() : Node("base_status_node")
    {
        publisher_ = this->create_publisher<std_msgs::msg::String>("/base/status", 10);
        timer_ = this->create_wall_timer(1s, std::bind(&BaseStatusNode::onTimer, this));

        RCLCPP_INFO(this->get_logger(), "base_status_node started");
    }
};

/**
 * @brief 程序入口函数。
 *
 * main 函数负责初始化 ROS2、创建 BaseStatusNode 节点、
 * 启动 ROS2 事件循环，并在程序退出前关闭 ROS2。
 *
 * @param argc 命令行参数数量。
 * @param argv 命令行参数数组。
 * @return int 程序退出码，0 表示正常退出。
 */

int main(int argc, char const *argv[])
{
    rclcpp::init(argc, argv);
    // 创建底盘状态发布节点对象
    auto node = std::make_shared<BaseStatusNode>();

    rclcpp::spin(node);

    rclcpp::shutdown();

    return 0;
}
