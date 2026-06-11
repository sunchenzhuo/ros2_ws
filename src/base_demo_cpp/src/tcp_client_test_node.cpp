/*
 * @Author: 树 shuxianshengio@126.com
 * @Date: 2026-06-10 18:12:09
 * @LastEditors: 树 shuxianshengio@126.com
 * @LastEditTime: 2026-06-11 15:11:26
 * @FilePath: /shu/ros2_ws/src/base_demo_cpp/src/tcp_client_test_node.cpp
 * @Description: 编写一个ROS2的一个tcp_client的测试阶段
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
   * 如果连接、发送或接收任意一步失败，函数会打印错误日志并直接返回。
   */
  void runOnce()
  {
    // 创建 TCP 客户端对象。
    // client 是局部变量，runOnce() 执行结束后会自动析构。
    // 如果 TcpClient 析构函数中实现了 closeSocket()，
    // 那么 TCP 连接也会自动关闭。
    TcpClient client;

    // 连接 TCP 服务端。
    // server_ip_ 和 server_port_ 来自 ROS2 参数。
    // 如果连接失败，打印错误日志并结束本次测试。
    if (!client.connectTo(server_ip_, server_port_))
    {
      RCLCPP_ERROR(
          this->get_logger(),
          "connect failed : %s:%d",
          server_ip_.c_str(),
          server_port_);
      return;
    }

    // 构造一条测试底盘控制命令。
    //
    // 协议格式示例：
    // CMD seq vx vy wz
    //
    // 含义：
    // - CMD：命令标识；
    // - 0：命令序号；
    // - 0.30：x 方向线速度 vx；
    // - 0.00：y 方向线速度 vy；
    // - 0.50：z 轴角速度 wz。
    std::string cmd = "CMD 0 0.30 0.00 0.50";

    // 打印发送日志。
    // TX 表示 transmit，即发送方向的数据。
    RCLCPP_INFO(
        this->get_logger(),
        "TX:%s",
        cmd.c_str());

    // 发送一行命令到 TCP 服务端。
    //
    // sendLine() 通常会在字符串末尾补充换行符 '\n'，
    // 或者要求传入的字符串本身符合“一行协议”格式。
    //
    // 如果发送失败，打印错误日志并结束本次测试。
    if (!client.sendLine(cmd))
    {
      RCLCPP_ERROR(
          this->get_logger(),
          "send failed");
      return;
    }

    // 用于保存服务端返回的一行响应数据。
    std::string reply;
    // 接收服务端返回的一行数据。
    //
    // receiveLine() 会从 TCP socket 中读取数据，
    // 直到读取到换行符 '\n'，表示一行响应结束。
    //
    // 注意：
    // 这里应该把接收结果保存到 reply 中，
    // 不是保存到 cmd 中。
    if (!client.receiveLine(reply))
    {
      RCLCPP_ERROR(
          this->get_logger(),
          "receive failed");
      return;
    }

    // 打印接收日志。
    // RX 表示 receive，即接收方向的数据。
    RCLCPP_INFO(
        this->get_logger(),
        "RX:%s",
        reply.c_str());
  }

public:
  /**
   * @brief TcpClientTestNode 构造函数。
   * 构造函数负责完成节点初始化，包括：
   * 1. 设置节点名称为 tcp_client_test_node；
   * 2. 声明 TCP 服务端 IP 参数；
   * 3. 声明 TCP 服务端端口参数；
   * 4. 读取参数值；
   * 5. 输出节点启动日志；
   * 6. 执行一次 TCP 通信测试。
   */
  TcpClientTestNode() : Node("tcp_client_test_node")
  {
    // 声明 TCP 服务端 IP 参数。
    //
    // 参数名：server_ip
    // 默认值：127.0.0.1
    this->declare_parameter<std::string>("server_ip", "127.0.0.1");

    // 声明 TCP 服务端端口参数。
    //
    // 参数名：server_port
    // 默认值：17000
    this->declare_parameter<int>("server_port", 17000);

    // 读取 server_ip 参数值。
    server_ip_ = this->get_parameter("server_ip").as_string();
    // 读取 server_port 参数值。
    server_port_ = this->get_parameter("server_port").as_int();

    // 打印节点启动日志和当前连接配置。
    RCLCPP_INFO(
        this->get_logger(),
        "tcp_client_test_node started , server_ip:%s server_port:%d",
        server_ip_.c_str(),
        server_port_);

    // 执行一次 TCP 通信测试。
    //
    // 因为这是一次性测试节点，没有订阅者、定时器等持续回调，
    // 所以可以直接在构造函数中调用 runOnce()。
    runOnce();
  }
};

/**
 * @brief 程序入口函数。
 * main 函数负责初始化 ROS2、创建 TcpClientTestNode 节点，
 * 执行一次 TCP 客户端测试，并在结束前关闭 ROS2。
 * 注意： * 本程序是一次性测试程序，runOnce() 已经在节点构造函数中执行。
 * 因此这里不需要 rclcpp::spin()。
 * 如果后续改造成周期测试、订阅触发测试或定时器测试，
 * 则需要使用 rclcpp::spin(node) 让节点持续运行。
 * @param argc 命令行参数数量。
 * @param argv 命令行参数数组。
 * @return int 程序退出码，0 表示正常退出。
 */
int main(int argc, char const *argv[])
{
  // 初始化 ROS2。
  // 所有 ROS2 C++ 程序在创建节点前都需要先调用 rclcpp::init()。
  rclcpp::init(argc, argv);

  // 创建 TCP 客户端测试节点。
  //
  // std::make_shared 用于创建 shared_ptr 智能指针，
  // 这是 ROS2 C++ 中管理节点对象生命周期的常见写法。
  auto node = std::make_shared<TcpClientTestNode>();
  // 关闭 ROS2。
  //
  // 因为该节点是一次性测试节点，构造函数中已经执行完 runOnce()，
  // 所以这里可以直接 shutdown。
  rclcpp::shutdown();
  return 0;
}
