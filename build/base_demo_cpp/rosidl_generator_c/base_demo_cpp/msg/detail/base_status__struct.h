// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from base_demo_cpp:msg/BaseStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "base_demo_cpp/msg/base_status.h"


#ifndef BASE_DEMO_CPP__MSG__DETAIL__BASE_STATUS__STRUCT_H_
#define BASE_DEMO_CPP__MSG__DETAIL__BASE_STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'err'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/BaseStatus in the package base_demo_cpp.
typedef struct base_demo_cpp__msg__BaseStatus
{
  int32_t seq;
  double vx;
  double vy;
  double wz;
  double battery_voltage;
  rosidl_runtime_c__String err;
  bool cmd_timeout;
} base_demo_cpp__msg__BaseStatus;

// Struct for a sequence of base_demo_cpp__msg__BaseStatus.
typedef struct base_demo_cpp__msg__BaseStatus__Sequence
{
  base_demo_cpp__msg__BaseStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} base_demo_cpp__msg__BaseStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // BASE_DEMO_CPP__MSG__DETAIL__BASE_STATUS__STRUCT_H_
