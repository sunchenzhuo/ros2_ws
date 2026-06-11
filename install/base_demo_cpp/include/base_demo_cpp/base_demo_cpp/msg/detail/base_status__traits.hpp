// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from base_demo_cpp:msg/BaseStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "base_demo_cpp/msg/base_status.hpp"


#ifndef BASE_DEMO_CPP__MSG__DETAIL__BASE_STATUS__TRAITS_HPP_
#define BASE_DEMO_CPP__MSG__DETAIL__BASE_STATUS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "base_demo_cpp/msg/detail/base_status__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace base_demo_cpp
{

namespace msg
{

inline void to_flow_style_yaml(
  const BaseStatus & msg,
  std::ostream & out)
{
  out << "{";
  // member: seq
  {
    out << "seq: ";
    rosidl_generator_traits::value_to_yaml(msg.seq, out);
    out << ", ";
  }

  // member: vx
  {
    out << "vx: ";
    rosidl_generator_traits::value_to_yaml(msg.vx, out);
    out << ", ";
  }

  // member: vy
  {
    out << "vy: ";
    rosidl_generator_traits::value_to_yaml(msg.vy, out);
    out << ", ";
  }

  // member: wz
  {
    out << "wz: ";
    rosidl_generator_traits::value_to_yaml(msg.wz, out);
    out << ", ";
  }

  // member: battery_voltage
  {
    out << "battery_voltage: ";
    rosidl_generator_traits::value_to_yaml(msg.battery_voltage, out);
    out << ", ";
  }

  // member: err
  {
    out << "err: ";
    rosidl_generator_traits::value_to_yaml(msg.err, out);
    out << ", ";
  }

  // member: cmd_timeout
  {
    out << "cmd_timeout: ";
    rosidl_generator_traits::value_to_yaml(msg.cmd_timeout, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const BaseStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: seq
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "seq: ";
    rosidl_generator_traits::value_to_yaml(msg.seq, out);
    out << "\n";
  }

  // member: vx
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "vx: ";
    rosidl_generator_traits::value_to_yaml(msg.vx, out);
    out << "\n";
  }

  // member: vy
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "vy: ";
    rosidl_generator_traits::value_to_yaml(msg.vy, out);
    out << "\n";
  }

  // member: wz
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "wz: ";
    rosidl_generator_traits::value_to_yaml(msg.wz, out);
    out << "\n";
  }

  // member: battery_voltage
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "battery_voltage: ";
    rosidl_generator_traits::value_to_yaml(msg.battery_voltage, out);
    out << "\n";
  }

  // member: err
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "err: ";
    rosidl_generator_traits::value_to_yaml(msg.err, out);
    out << "\n";
  }

  // member: cmd_timeout
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "cmd_timeout: ";
    rosidl_generator_traits::value_to_yaml(msg.cmd_timeout, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const BaseStatus & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace base_demo_cpp

namespace rosidl_generator_traits
{

[[deprecated("use base_demo_cpp::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const base_demo_cpp::msg::BaseStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  base_demo_cpp::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use base_demo_cpp::msg::to_yaml() instead")]]
inline std::string to_yaml(const base_demo_cpp::msg::BaseStatus & msg)
{
  return base_demo_cpp::msg::to_yaml(msg);
}

template<>
inline const char * data_type<base_demo_cpp::msg::BaseStatus>()
{
  return "base_demo_cpp::msg::BaseStatus";
}

template<>
inline const char * name<base_demo_cpp::msg::BaseStatus>()
{
  return "base_demo_cpp/msg/BaseStatus";
}

template<>
struct has_fixed_size<base_demo_cpp::msg::BaseStatus>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<base_demo_cpp::msg::BaseStatus>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<base_demo_cpp::msg::BaseStatus>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // BASE_DEMO_CPP__MSG__DETAIL__BASE_STATUS__TRAITS_HPP_
