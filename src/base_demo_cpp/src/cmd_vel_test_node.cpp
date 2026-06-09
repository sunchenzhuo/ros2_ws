/**
 * @文件路径         : /shu/ros2_ws/src/base_demo_cpp/src/cmd_vel_test_node.cpp
 * @作者           : 树
 * @创建时间         : 2026-06-09 16:54:00
 * @最后编辑         : 树
 * @最后编辑时间       : 2026-06-09 17:45:14
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

private:
    void onTimer()
    {
        geometry_msgs::msg::Twist msg;

        msg.linear.x = 0.30;
        msg.linear.y = 0.00;
        msg.angular.z = 0.50;

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
        pub_ = this->create_publisher<geometry_msgs::msg::Twist>("/cmd_vel", 10);
        timer_ = this->create_wall_timer(200ms, std::bind(&CmdVelTestNode::onTimer, this));
        RCLCPP_INFO(this->get_logger(), "cmd_vel_test_node strated");
    }
};

int main(int argc, char const *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<CmdVelTestNode>());
    rclcpp::shutdown();
    return 0;
}
