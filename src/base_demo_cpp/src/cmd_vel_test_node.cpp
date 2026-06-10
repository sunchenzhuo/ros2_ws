/*
 * @Author: 树 shuxianshengio@126.com
 * @Date: 2026-06-09 16:54:00
 * @LastEditors: 树 shuxianshengio@126.com
 * @LastEditTime: 2026-06-10 14:14:33
 * @FilePath: /shu/ros2_ws/src/base_demo_cpp/src/cmd_vel_test_node.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
/**
 * @文件路径         : /shu/ros2_ws/src/base_demo_cpp/src/cmd_vel_test_node.cpp
 * @作者           : 树
 * @创建时间         : 2026-06-09 16:54:00
 * @最后编辑         : 树
 * @最后编辑时间       : 2026-06-10 10:20:14
 * @Version      : V1.0.0
 * @功能描述         :一个测试节点
 * @Copyright    : Copyright (c) 2026 by 树, All Rights Reserved.
 */
#include <memory>
#include <chrono>

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"

using namespace std::chrono_literals;

class CmdVelTestNode : public rclcpp::Node
{
private:
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr pub_;
  rclcpp::TimerBase::SharedPtr timer_;
  double test_vx_ = 0.30;
  double test_vy_ = 0.00;
  double test_wz_ = 0.50;
  int publish_period_ms_ = 200;

private:
  void onTimer()
  {
    geometry_msgs::msg::Twist msg;

    msg.linear.x = test_vx_;
    msg.linear.y = test_vy_;
    msg.linear.z = 0.0;

    msg.angular.x = 0.0;
    msg.angular.y = 0.0;
    msg.angular.z = test_wz_;

    pub_->publish(msg);

    RCLCPP_INFO(this->get_logger(),
                "publish /cmd_vel vx=%.2f vy=%.2f wz=%.2f",
                msg.linear.x,
                msg.linear.y,
                msg.angular.z);
  }

public:
  CmdVelTestNode() : Node("cmd_vel_node_test")
  {
    this->declare_parameter<double>("test_vx", 0.30);
    this->declare_parameter<double>("test_vy", 0.00);
    this->declare_parameter<double>("test_wz", 0.50);
    this->declare_parameter<int>("publish_period_ms", 200);

    test_vx_ = this->get_parameter("test_vx").as_double();
    test_vy_ = this->get_parameter("test_vy").as_double();
    test_wz_ = this->get_parameter("test_wz").as_double();
    publish_period_ms_ = this->get_parameter("publish_period_ms").as_int();
    pub_ = this->create_publisher<geometry_msgs::msg::Twist>("/cmd_vel", 10);
    timer_ = this->create_wall_timer(
        std::chrono::milliseconds(publish_period_ms_),
        std::bind(&CmdVelTestNode::onTimer, this));
    RCLCPP_INFO(
        this->get_logger(),
        "cmd_vel_test_node started,test_vx=%.2f test_vy=%.2f test_wz=%.2f publish_period_ms=%d",
        test_vx_,
        test_vy_,
        test_wz_,
        publish_period_ms_);
  }
};

int main(int argc, char const *argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<CmdVelTestNode>());
  rclcpp::shutdown();
  return 0;
}
