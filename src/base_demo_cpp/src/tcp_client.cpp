/*
 * @Author: 树 shuxianshengio@126.com
 * @Date: 2026-06-10 15:06:48
 * @LastEditors: 树 shuxianshengio@126.com
 * @LastEditTime: 2026-06-10 15:55:52
 * @FilePath: /shu/ros2_ws/src/base_demo_cpp/src/to_client.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */

#include "base_demo_cpp/tcp_client.hpp"

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>

TcpClient::TcpClient() : sock_fd_(-1)
{
}
TcpClient::~TcpClient()
{
  closeSocket();
}

bool TcpClient::connectTo(const std::string host, int port)
{
  closeSocket();

  sock_fd_ = socket(AF_INET, SOCK_STREAM, 0);
  if (sock_fd_ < 0)
  {
    return false;
  }

  sockaddr_in server_addr;
  std::memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);

  if (inet_pton(AF_INET, host.c_str(), &server_addr.sin_addr))
  {
    closeSocket();
    return false;
  }

  if (connect(sock_fd_, reinterpret_cast<sockaddr *>(&server_addr), sizeof(server_addr)))
  {
    closeSocket();
    return false;
  }
  return true;
}

bool TcpClient::sendLine(const std::string &line)
{
  if (sock_fd_ < 0)
  {
    return false;
  }
  std::string data = line;
  if (data.empty() || data.back() != '\n')
  {
    data.push_back('\n');
  }

  const char *buffer = data.c_str();
  size_t total_sent = 0;
  size_t total_szie = data.size();

  while (total_sent < total_szie)
  {
    ssize_t sent = send(sock_fd_, buffer + total_sent, total_szie - total_sent, 0);
    if (sent < 0)
    {
      closeSocket();
      return false;
    }
    total_sent += static_cast<size_t>(sent);
  }
  return true;
}
bool TcpClient::receiveLine(std::string &line)
{
  line.clear();

  if (sock_fd_ < 0)
  {
    return false;
  }
  char ch = '\0';

  while (true)
  {
    ssize_t n = recv(sock_fd_, &ch, 1, 0);
    if (n < 0)
    {
      closeSocket();
      return false;
    }

    if (ch == '\n')
    {
      break;
    }
    line.push_back(ch);
  }
  return true;
}
void TcpClient::closeSocket()
{
  if (sock_fd_ > 0)
  {
    close(sock_fd_);
    sock_fd_ = -1;
  }
}
bool TcpClient::isConnented() const
{
  return sock_fd_ > 0;
}