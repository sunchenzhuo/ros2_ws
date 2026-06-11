// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from base_demo_cpp:msg/BaseStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "base_demo_cpp/msg/base_status.hpp"


#ifndef BASE_DEMO_CPP__MSG__DETAIL__BASE_STATUS__BUILDER_HPP_
#define BASE_DEMO_CPP__MSG__DETAIL__BASE_STATUS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "base_demo_cpp/msg/detail/base_status__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace base_demo_cpp
{

namespace msg
{

namespace builder
{

class Init_BaseStatus_cmd_timeout
{
public:
  explicit Init_BaseStatus_cmd_timeout(::base_demo_cpp::msg::BaseStatus & msg)
  : msg_(msg)
  {}
  ::base_demo_cpp::msg::BaseStatus cmd_timeout(::base_demo_cpp::msg::BaseStatus::_cmd_timeout_type arg)
  {
    msg_.cmd_timeout = std::move(arg);
    return std::move(msg_);
  }

private:
  ::base_demo_cpp::msg::BaseStatus msg_;
};

class Init_BaseStatus_err
{
public:
  explicit Init_BaseStatus_err(::base_demo_cpp::msg::BaseStatus & msg)
  : msg_(msg)
  {}
  Init_BaseStatus_cmd_timeout err(::base_demo_cpp::msg::BaseStatus::_err_type arg)
  {
    msg_.err = std::move(arg);
    return Init_BaseStatus_cmd_timeout(msg_);
  }

private:
  ::base_demo_cpp::msg::BaseStatus msg_;
};

class Init_BaseStatus_battery_voltage
{
public:
  explicit Init_BaseStatus_battery_voltage(::base_demo_cpp::msg::BaseStatus & msg)
  : msg_(msg)
  {}
  Init_BaseStatus_err battery_voltage(::base_demo_cpp::msg::BaseStatus::_battery_voltage_type arg)
  {
    msg_.battery_voltage = std::move(arg);
    return Init_BaseStatus_err(msg_);
  }

private:
  ::base_demo_cpp::msg::BaseStatus msg_;
};

class Init_BaseStatus_wz
{
public:
  explicit Init_BaseStatus_wz(::base_demo_cpp::msg::BaseStatus & msg)
  : msg_(msg)
  {}
  Init_BaseStatus_battery_voltage wz(::base_demo_cpp::msg::BaseStatus::_wz_type arg)
  {
    msg_.wz = std::move(arg);
    return Init_BaseStatus_battery_voltage(msg_);
  }

private:
  ::base_demo_cpp::msg::BaseStatus msg_;
};

class Init_BaseStatus_vy
{
public:
  explicit Init_BaseStatus_vy(::base_demo_cpp::msg::BaseStatus & msg)
  : msg_(msg)
  {}
  Init_BaseStatus_wz vy(::base_demo_cpp::msg::BaseStatus::_vy_type arg)
  {
    msg_.vy = std::move(arg);
    return Init_BaseStatus_wz(msg_);
  }

private:
  ::base_demo_cpp::msg::BaseStatus msg_;
};

class Init_BaseStatus_vx
{
public:
  explicit Init_BaseStatus_vx(::base_demo_cpp::msg::BaseStatus & msg)
  : msg_(msg)
  {}
  Init_BaseStatus_vy vx(::base_demo_cpp::msg::BaseStatus::_vx_type arg)
  {
    msg_.vx = std::move(arg);
    return Init_BaseStatus_vy(msg_);
  }

private:
  ::base_demo_cpp::msg::BaseStatus msg_;
};

class Init_BaseStatus_seq
{
public:
  Init_BaseStatus_seq()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_BaseStatus_vx seq(::base_demo_cpp::msg::BaseStatus::_seq_type arg)
  {
    msg_.seq = std::move(arg);
    return Init_BaseStatus_vx(msg_);
  }

private:
  ::base_demo_cpp::msg::BaseStatus msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::base_demo_cpp::msg::BaseStatus>()
{
  return base_demo_cpp::msg::builder::Init_BaseStatus_seq();
}

}  // namespace base_demo_cpp

#endif  // BASE_DEMO_CPP__MSG__DETAIL__BASE_STATUS__BUILDER_HPP_
