/**
 * @文件路径         : /shu/ros2_ws/src/base_demo_cpp/src/base_status_listener_node.cpp
 * @作者           : 树
 * @创建时间         : 2026-06-09 10:06:41
 * @最后编辑         : 树
 * @最后编辑时间       : 2026-06-09 14:28:59
 * @Version      : V1.0.0
 * @功能描述         :订阅 /base/status 消息类型 base_demo_cpp/msg/BaseStatus  读取 seq / vx / vy / wz / battery_voltage / err / cmd_timeout   根据 cmd_timeout 和 battery_voltage 打印状态判断
 * @Copyright    : Copyright (c) 2026 by 树, All Rights Reserved.
 */

#include <memory>

#include "base_demo_cpp/msg/base_status.hpp"
#include "rclcpp/rclcpp.hpp"

class BaseStatusListenerNode : public rclcpp::Node
{
private:
    rclcpp::Subscription<base_demo_cpp::msg::BaseStatus>::SharedPtr sub_;

private:
    void onStatus(const base_demo_cpp::msg::BaseStatus::SharedPtr msg)
    {
        RCLCPP_INFO(
            this->get_logger(),
            "status seq:%d vx=%.2f vy=%.2f wz=%.2f battery_voltage=%.2f err=%s cmd_timeout=%d",
            msg->seq,
            msg->vx,
            msg->vy,
            msg->wz,
            msg->battery_voltage,
            msg->err.c_str(),
            msg->cmd_timeout ? 1 : 0);

        if (msg->cmd_timeout)
        {
            RCLCPP_WARN(this->get_logger(), "base command timeout, chassis should be stopped");
        }

        if (msg->battery_voltage < 11.0)
        {
            RCLCPP_WARN(this->get_logger(), "batter voltage low:%.2f", msg->battery_voltage);
        }
    }

public:
    BaseStatusListenerNode() : Node("base_status_listener_node")
    {
        sub_ = this->create_subscription<base_demo_cpp::msg::BaseStatus>(
            "base/status",
            10,
            std::bind(&BaseStatusListenerNode::onStatus, this, std::placeholders::_1));

        RCLCPP_INFO(this->get_logger(), "base_status_listener_node started");
    }
};
int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<BaseStatusListenerNode>());
    rclcpp::shutdown();
    return 0;
}
