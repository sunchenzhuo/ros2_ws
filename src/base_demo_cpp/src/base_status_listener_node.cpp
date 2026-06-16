/*
 * @Author: 树 shuxianshengio@126.com
 * @Date: 2026-06-09 10:06:41
 * @LastEditors: 树 shuxianshengio@126.com
 * @LastEditTime: 2026-06-16 14:39:38
 * @FilePath: /shu/agv-robot-system/ros2_ws/src/base_demo_cpp/src/base_status_listener_node.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
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
  std::string status_reliability_ = "reliable";
  int status_depth_ = 10;

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
    this->declare_parameter<std::string>("status_reliability", "reliable");
    this->declare_parameter<int>("status_depth", 10);

    status_reliability_ = this->get_parameter("status_reliability").as_string();
    status_depth_ = this->get_parameter("status_depth").as_int();

    if (status_depth_ <= 0)
    {
      RCLCPP_WARN(
          this->get_logger(),
          "invalid status_depth = %d ,user default 10",
          status_depth_);
      status_depth_ = 10;
    }

    rclcpp::QoS status_qos(status_depth_);
    if (status_reliability_ == "best_effort")
    {
      status_qos.best_effort();
    }
    else
    {
      status_qos.reliable();
    }
    sub_ = this->create_subscription<base_demo_cpp::msg::BaseStatus>(
        "/base/status",
        status_qos,
        std::bind(&BaseStatusListenerNode::onStatus, this, std::placeholders::_1));

    RCLCPP_INFO(this->get_logger(),
                "status subscriber qos reliability=%s depth=%d",
                status_reliability_.c_str(),
                status_depth_);
  }
};
int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<BaseStatusListenerNode>());
  rclcpp::shutdown();
  return 0;
}
