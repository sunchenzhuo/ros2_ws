/*
 * @Author: 树 shuxianshengio@126.com
 * @Date: 2026-06-10 14:51:36
 * @LastEditors: 树 shuxianshengio@126.com
 * @LastEditTime: 2026-06-11 15:04:50
 * @FilePath: /shu/ros2_ws/include/base_demo_cpp/to_client.hpp
 * @Description: client的头文件
 */
#pragma once

#include <string>

class TcpClient
{
private:
  int sock_fd_;

public:
  TcpClient();
  ~TcpClient();
  TcpClient(const TcpClient &) = delete;
  TcpClient &operator=(const TcpClient &) = delete;

  bool connectTo(const std::string host, int port);
  bool sendLine(const std::string &line);
  bool receiveLine(std::string &line);
  void closeSocket();
  bool isConnected() const;
};