// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from base_demo_cpp:msg/BaseStatus.idl
// generated code does not contain a copyright notice
#include "base_demo_cpp/msg/detail/base_status__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <cstddef>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/serialization_helpers.hpp"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "base_demo_cpp/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "base_demo_cpp/msg/detail/base_status__struct.h"
#include "base_demo_cpp/msg/detail/base_status__functions.h"
#include "fastcdr/Cdr.h"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif

#include "rosidl_runtime_c/string.h"  // err
#include "rosidl_runtime_c/string_functions.h"  // err

// forward declare type support functions


using _BaseStatus__ros_msg_type = base_demo_cpp__msg__BaseStatus;


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_base_demo_cpp
bool cdr_serialize_base_demo_cpp__msg__BaseStatus(
  const base_demo_cpp__msg__BaseStatus * ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Field name: seq
  {
    cdr << ros_message->seq;
  }

  // Field name: vx
  {
    cdr << ros_message->vx;
  }

  // Field name: vy
  {
    cdr << ros_message->vy;
  }

  // Field name: wz
  {
    cdr << ros_message->wz;
  }

  // Field name: battery_voltage
  {
    cdr << ros_message->battery_voltage;
  }

  // Field name: err
  {
    const rosidl_runtime_c__String * str = &ros_message->err;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  // Field name: cmd_timeout
  {
    cdr << (ros_message->cmd_timeout ? true : false);
  }

  return true;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_base_demo_cpp
bool cdr_deserialize_base_demo_cpp__msg__BaseStatus(
  eprosima::fastcdr::Cdr & cdr,
  base_demo_cpp__msg__BaseStatus * ros_message)
{
  // Field name: seq
  {
    cdr >> ros_message->seq;
  }

  // Field name: vx
  {
    cdr >> ros_message->vx;
  }

  // Field name: vy
  {
    cdr >> ros_message->vy;
  }

  // Field name: wz
  {
    cdr >> ros_message->wz;
  }

  // Field name: battery_voltage
  {
    cdr >> ros_message->battery_voltage;
  }

  // Field name: err
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->err.data) {
      rosidl_runtime_c__String__init(&ros_message->err);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->err,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'err'\n");
      return false;
    }
  }

  // Field name: cmd_timeout
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->cmd_timeout = tmp ? true : false;
  }

  return true;
}  // NOLINT(readability/fn_size)


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_base_demo_cpp
size_t get_serialized_size_base_demo_cpp__msg__BaseStatus(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _BaseStatus__ros_msg_type * ros_message = static_cast<const _BaseStatus__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Field name: seq
  {
    size_t item_size = sizeof(ros_message->seq);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: vx
  {
    size_t item_size = sizeof(ros_message->vx);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: vy
  {
    size_t item_size = sizeof(ros_message->vy);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: wz
  {
    size_t item_size = sizeof(ros_message->wz);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: battery_voltage
  {
    size_t item_size = sizeof(ros_message->battery_voltage);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: err
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->err.size + 1);

  // Field name: cmd_timeout
  {
    size_t item_size = sizeof(ros_message->cmd_timeout);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_base_demo_cpp
size_t max_serialized_size_base_demo_cpp__msg__BaseStatus(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;

  // Field name: seq
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Field name: vx
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: vy
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: wz
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: battery_voltage
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: err
  {
    size_t array_size = 1;
    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }

  // Field name: cmd_timeout
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }


  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = base_demo_cpp__msg__BaseStatus;
    is_plain =
      (
      offsetof(DataType, cmd_timeout) +
      last_member_size
      ) == ret_val;
  }
  return ret_val;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_base_demo_cpp
bool cdr_serialize_key_base_demo_cpp__msg__BaseStatus(
  const base_demo_cpp__msg__BaseStatus * ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Field name: seq
  {
    cdr << ros_message->seq;
  }

  // Field name: vx
  {
    cdr << ros_message->vx;
  }

  // Field name: vy
  {
    cdr << ros_message->vy;
  }

  // Field name: wz
  {
    cdr << ros_message->wz;
  }

  // Field name: battery_voltage
  {
    cdr << ros_message->battery_voltage;
  }

  // Field name: err
  {
    const rosidl_runtime_c__String * str = &ros_message->err;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  // Field name: cmd_timeout
  {
    cdr << (ros_message->cmd_timeout ? true : false);
  }

  return true;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_base_demo_cpp
size_t get_serialized_size_key_base_demo_cpp__msg__BaseStatus(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _BaseStatus__ros_msg_type * ros_message = static_cast<const _BaseStatus__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;

  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Field name: seq
  {
    size_t item_size = sizeof(ros_message->seq);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: vx
  {
    size_t item_size = sizeof(ros_message->vx);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: vy
  {
    size_t item_size = sizeof(ros_message->vy);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: wz
  {
    size_t item_size = sizeof(ros_message->wz);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: battery_voltage
  {
    size_t item_size = sizeof(ros_message->battery_voltage);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: err
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->err.size + 1);

  // Field name: cmd_timeout
  {
    size_t item_size = sizeof(ros_message->cmd_timeout);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_base_demo_cpp
size_t max_serialized_size_key_base_demo_cpp__msg__BaseStatus(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;
  // Field name: seq
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Field name: vx
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: vy
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: wz
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: battery_voltage
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: err
  {
    size_t array_size = 1;
    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }

  // Field name: cmd_timeout
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = base_demo_cpp__msg__BaseStatus;
    is_plain =
      (
      offsetof(DataType, cmd_timeout) +
      last_member_size
      ) == ret_val;
  }
  return ret_val;
}


static bool _BaseStatus__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const base_demo_cpp__msg__BaseStatus * ros_message = static_cast<const base_demo_cpp__msg__BaseStatus *>(untyped_ros_message);
  (void)ros_message;
  return cdr_serialize_base_demo_cpp__msg__BaseStatus(ros_message, cdr);
}

static bool _BaseStatus__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  base_demo_cpp__msg__BaseStatus * ros_message = static_cast<base_demo_cpp__msg__BaseStatus *>(untyped_ros_message);
  (void)ros_message;
  return cdr_deserialize_base_demo_cpp__msg__BaseStatus(cdr, ros_message);
}

static uint32_t _BaseStatus__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_base_demo_cpp__msg__BaseStatus(
      untyped_ros_message, 0));
}

static size_t _BaseStatus__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_base_demo_cpp__msg__BaseStatus(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_BaseStatus = {
  "base_demo_cpp::msg",
  "BaseStatus",
  _BaseStatus__cdr_serialize,
  _BaseStatus__cdr_deserialize,
  _BaseStatus__get_serialized_size,
  _BaseStatus__max_serialized_size,
  nullptr
};

static rosidl_message_type_support_t _BaseStatus__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_BaseStatus,
  get_message_typesupport_handle_function,
  &base_demo_cpp__msg__BaseStatus__get_type_hash,
  &base_demo_cpp__msg__BaseStatus__get_type_description,
  &base_demo_cpp__msg__BaseStatus__get_type_description_sources,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, base_demo_cpp, msg, BaseStatus)() {
  return &_BaseStatus__type_support;
}

#if defined(__cplusplus)
}
#endif
