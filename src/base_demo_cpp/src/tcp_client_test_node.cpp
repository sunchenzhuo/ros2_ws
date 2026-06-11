/*
 * @Author: 树 shuxianshengio@126.com
 * @Date: 2026-06-10 18:12:09
 * @LastEditors: 树 shuxianshengio@126.com
 * @LastEditTime: 2026-06-11 14:16:57
 * @FilePath: /shu/ros2_ws/src/base_demo_cpp/src/tcp_client_test_node.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */

#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "base_demo_cpp/tcp_client.hpp"

/** * @brief TCP 客户端测试节点。
 *
 *  TcpClientTestNode 继承自 rclcpp::Node，表示它是一个 ROS2 节点。
 * 该节点用于测试自定义 TcpClient 类是否可以正常完成：
 * 1. 连接 TCP 服务端；
 * 2. 发送一条底盘控制命令；
 * 3. 接收服务端返回数据；
 * 4. 输出发送和接收日志。
 * 该节点不是周期运行节点，而是一个“一次性测试节点”。
 * 节点启动后会在构造函数中调用 runOnce()，完成一次 TCP 通信测试。 */

class TcpClientTestNode : public rclcpp::Node
{
private:
  /**
   * @brief TCP 服务端 IP 地址。
   * 默认值为 127.0.0.1，表示连接本机 TCP 服务端。
   * 可以通过 ROS2 参数 server_ip 修改。 */
  std::string server_ip_;
  /**
   * @brief TCP 服务端端口号。
   * 默认值为 17000。
   * 可以通过 ROS2 参数  server_port 修改。 */
  int server_port_;

private:
  /**
   * @brief 执行一次 TCP 通信测试。
   * 该函数会创建一个 TcpClient 对象，并按照以下流程执行：
   * 1. 连接 TCP 服务端；
   * 2. 构造一条测试控制命令；
   * 3. 发送命令到服务端；
   * 4. 接收服务端返回的一行响应；
   * 5. 打印发送和接收日志。
   * 如果连接、发送或接收任意一步失败，函数会打印错误日志并直接返回。 */
  void runOnce()
  {
    TcpClient client;
    if (!client.connectTo(server_ip_, server_port_))
    {
      RCLCPP_ERROR(
          this->get_logger(),
          "connect failed : %s:%d",
          server_ip_.c_str(),
          server_port_);
      return;
    }
    std::string cmd = "CMD 0 0.30 0.00 0.50";
    RCLCPP_INFO(
        this->get_logger(),
        "TX:%s",
        cmd.c_str());

    if (!client.sendLine(cmd))
    {
      RCLCPP_ERROR(
          this->get_logger(),
          "send failed");
      return;
    }

    std::string reply;
    if (!client.receiveLine(cmd))
    {
      RCLCPP_ERROR(
          this->get_logger(),
          "receive failed");
      return;
    }
    RCLCPP_INFO(
        this->get_logger(),
        "TX:%s",
        reply.c_str());
  }

public:
  TcpClientTestNode() : Node("tcp_client_test_node")
  {
    this->declare_parameter<std::string>("server_ip", "127.0.0.1");
    this->declare_parameter<int>("server_port", 17000);

    server_ip_ = this->get_parameter("server_ip").as_string();
    server_port_ = this->get_parameter("server_port").as_int();

    RCLCPP_INFO(
        this->get_logger(),
        "tcp_client_test_node started , server_ip:%s server_port:%d",
        server_ip_.c_str(),
        server_port_);

    runOnce();
  }
};

int main(int argc, char const *argv[])
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<TcpClientTestNode>();
  rclcpp::shutdown();
  return 0;
}
