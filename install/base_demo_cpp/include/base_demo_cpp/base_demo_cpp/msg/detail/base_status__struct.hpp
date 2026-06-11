// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from base_demo_cpp:msg/BaseStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "base_demo_cpp/msg/base_status.hpp"


#ifndef BASE_DEMO_CPP__MSG__DETAIL__BASE_STATUS__STRUCT_HPP_
#define BASE_DEMO_CPP__MSG__DETAIL__BASE_STATUS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__base_demo_cpp__msg__BaseStatus __attribute__((deprecated))
#else
# define DEPRECATED__base_demo_cpp__msg__BaseStatus __declspec(deprecated)
#endif

namespace base_demo_cpp
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct BaseStatus_
{
  using Type = BaseStatus_<ContainerAllocator>;

  explicit BaseStatus_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->seq = 0l;
      this->vx = 0.0;
      this->vy = 0.0;
      this->wz = 0.0;
      this->battery_voltage = 0.0;
      this->err = "";
      this->cmd_timeout = false;
    }
  }

  explicit BaseStatus_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : err(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->seq = 0l;
      this->vx = 0.0;
      this->vy = 0.0;
      this->wz = 0.0;
      this->battery_voltage = 0.0;
      this->err = "";
      this->cmd_timeout = false;
    }
  }

  // field types and members
  using _seq_type =
    int32_t;
  _seq_type seq;
  using _vx_type =
    double;
  _vx_type vx;
  using _vy_type =
    double;
  _vy_type vy;
  using _wz_type =
    double;
  _wz_type wz;
  using _battery_voltage_type =
    double;
  _battery_voltage_type battery_voltage;
  using _err_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _err_type err;
  using _cmd_timeout_type =
    bool;
  _cmd_timeout_type cmd_timeout;

  // setters for named parameter idiom
  Type & set__seq(
    const int32_t & _arg)
  {
    this->seq = _arg;
    return *this;
  }
  Type & set__vx(
    const double & _arg)
  {
    this->vx = _arg;
    return *this;
  }
  Type & set__vy(
    const double & _arg)
  {
    this->vy = _arg;
    return *this;
  }
  Type & set__wz(
    const double & _arg)
  {
    this->wz = _arg;
    return *this;
  }
  Type & set__battery_voltage(
    const double & _arg)
  {
    this->battery_voltage = _arg;
    return *this;
  }
  Type & set__err(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->err = _arg;
    return *this;
  }
  Type & set__cmd_timeout(
    const bool & _arg)
  {
    this->cmd_timeout = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    base_demo_cpp::msg::BaseStatus_<ContainerAllocator> *;
  using ConstRawPtr =
    const base_demo_cpp::msg::BaseStatus_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<base_demo_cpp::msg::BaseStatus_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<base_demo_cpp::msg::BaseStatus_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      base_demo_cpp::msg::BaseStatus_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<base_demo_cpp::msg::BaseStatus_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      base_demo_cpp::msg::BaseStatus_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<base_demo_cpp::msg::BaseStatus_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<base_demo_cpp::msg::BaseStatus_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<base_demo_cpp::msg::BaseStatus_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__base_demo_cpp__msg__BaseStatus
    std::shared_ptr<base_demo_cpp::msg::BaseStatus_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__base_demo_cpp__msg__BaseStatus
    std::shared_ptr<base_demo_cpp::msg::BaseStatus_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const BaseStatus_ & other) const
  {
    if (this->seq != other.seq) {
      return false;
    }
    if (this->vx != other.vx) {
      return false;
    }
    if (this->vy != other.vy) {
      return false;
    }
    if (this->wz != other.wz) {
      return false;
    }
    if (this->battery_voltage != other.battery_voltage) {
      return false;
    }
    if (this->err != other.err) {
      return false;
    }
    if (this->cmd_timeout != other.cmd_timeout) {
      return false;
    }
    return true;
  }
  bool operator!=(const BaseStatus_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct BaseStatus_

// alias to use template instance with default allocator
using BaseStatus =
  base_demo_cpp::msg::BaseStatus_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace base_demo_cpp

#endif  // BASE_DEMO_CPP__MSG__DETAIL__BASE_STATUS__STRUCT_HPP_
