// generated from rosidl_typesupport_fastrtps_c/resource/idl__rosidl_typesupport_fastrtps_c.h.em
// with input from base_demo_cpp:msg/BaseStatus.idl
// generated code does not contain a copyright notice
#ifndef BASE_DEMO_CPP__MSG__DETAIL__BASE_STATUS__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
#define BASE_DEMO_CPP__MSG__DETAIL__BASE_STATUS__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_


#include <stddef.h>
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "base_demo_cpp/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "base_demo_cpp/msg/detail/base_status__struct.h"
#include "fastcdr/Cdr.h"

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_base_demo_cpp
bool cdr_serialize_base_demo_cpp__msg__BaseStatus(
  const base_demo_cpp__msg__BaseStatus * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_base_demo_cpp
bool cdr_deserialize_base_demo_cpp__msg__BaseStatus(
  eprosima::fastcdr::Cdr &,
  base_demo_cpp__msg__BaseStatus * ros_message);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_base_demo_cpp
size_t get_serialized_size_base_demo_cpp__msg__BaseStatus(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_base_demo_cpp
size_t max_serialized_size_base_demo_cpp__msg__BaseStatus(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_base_demo_cpp
bool cdr_serialize_key_base_demo_cpp__msg__BaseStatus(
  const base_demo_cpp__msg__BaseStatus * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_base_demo_cpp
size_t get_serialized_size_key_base_demo_cpp__msg__BaseStatus(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_base_demo_cpp
size_t max_serialized_size_key_base_demo_cpp__msg__BaseStatus(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_base_demo_cpp
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, base_demo_cpp, msg, BaseStatus)();

#ifdef __cplusplus
}
#endif

#endif  // BASE_DEMO_CPP__MSG__DETAIL__BASE_STATUS__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
