// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from base_demo_cpp:msg/BaseStatus.idl
// generated code does not contain a copyright notice
#include "base_demo_cpp/msg/detail/base_status__rosidl_typesupport_fastrtps_cpp.hpp"
#include "base_demo_cpp/msg/detail/base_status__functions.h"
#include "base_demo_cpp/msg/detail/base_status__struct.hpp"

#include <cstddef>
#include <limits>
#include <stdexcept>
#include <string>
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_fastrtps_cpp/identifier.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_fastrtps_cpp/serialization_helpers.hpp"
#include "rosidl_typesupport_fastrtps_cpp/wstring_conversion.hpp"
#include "fastcdr/Cdr.h"


// forward declaration of message dependencies and their conversion functions

namespace base_demo_cpp
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{


bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_base_demo_cpp
cdr_serialize(
  const base_demo_cpp::msg::BaseStatus & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: seq
  cdr << ros_message.seq;

  // Member: vx
  cdr << ros_message.vx;

  // Member: vy
  cdr << ros_message.vy;

  // Member: wz
  cdr << ros_message.wz;

  // Member: battery_voltage
  cdr << ros_message.battery_voltage;

  // Member: err
  cdr << ros_message.err;

  // Member: cmd_timeout
  cdr << (ros_message.cmd_timeout ? true : false);

  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_base_demo_cpp
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  base_demo_cpp::msg::BaseStatus & ros_message)
{
  // Member: seq
  cdr >> ros_message.seq;

  // Member: vx
  cdr >> ros_message.vx;

  // Member: vy
  cdr >> ros_message.vy;

  // Member: wz
  cdr >> ros_message.wz;

  // Member: battery_voltage
  cdr >> ros_message.battery_voltage;

  // Member: err
  cdr >> ros_message.err;

  // Member: cmd_timeout
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.cmd_timeout = tmp ? true : false;
  }

  return true;
}  // NOLINT(readability/fn_size)


size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_base_demo_cpp
get_serialized_size(
  const base_demo_cpp::msg::BaseStatus & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: seq
  {
    size_t item_size = sizeof(ros_message.seq);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Member: vx
  {
    size_t item_size = sizeof(ros_message.vx);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Member: vy
  {
    size_t item_size = sizeof(ros_message.vy);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Member: wz
  {
    size_t item_size = sizeof(ros_message.wz);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Member: battery_voltage
  {
    size_t item_size = sizeof(ros_message.battery_voltage);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Member: err
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message.err.size() + 1);

  // Member: cmd_timeout
  {
    size_t item_size = sizeof(ros_message.cmd_timeout);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}


size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_base_demo_cpp
max_serialized_size_BaseStatus(
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

  // Member: seq
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // Member: vx
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }
  // Member: vy
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }
  // Member: wz
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }
  // Member: battery_voltage
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }
  // Member: err
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
  // Member: cmd_timeout
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
    using DataType = base_demo_cpp::msg::BaseStatus;
    is_plain =
      (
      offsetof(DataType, cmd_timeout) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_base_demo_cpp
cdr_serialize_key(
  const base_demo_cpp::msg::BaseStatus & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: seq
  cdr << ros_message.seq;

  // Member: vx
  cdr << ros_message.vx;

  // Member: vy
  cdr << ros_message.vy;

  // Member: wz
  cdr << ros_message.wz;

  // Member: battery_voltage
  cdr << ros_message.battery_voltage;

  // Member: err
  cdr << ros_message.err;

  // Member: cmd_timeout
  cdr << (ros_message.cmd_timeout ? true : false);

  return true;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_base_demo_cpp
get_serialized_size_key(
  const base_demo_cpp::msg::BaseStatus & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: seq
  {
    size_t item_size = sizeof(ros_message.seq);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Member: vx
  {
    size_t item_size = sizeof(ros_message.vx);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Member: vy
  {
    size_t item_size = sizeof(ros_message.vy);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Member: wz
  {
    size_t item_size = sizeof(ros_message.wz);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Member: battery_voltage
  {
    size_t item_size = sizeof(ros_message.battery_voltage);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Member: err
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message.err.size() + 1);

  // Member: cmd_timeout
  {
    size_t item_size = sizeof(ros_message.cmd_timeout);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_base_demo_cpp
max_serialized_size_key_BaseStatus(
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

  // Member: seq
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: vx
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Member: vy
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Member: wz
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Member: battery_voltage
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Member: err
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

  // Member: cmd_timeout
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
    using DataType = base_demo_cpp::msg::BaseStatus;
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
  auto typed_message =
    static_cast<const base_demo_cpp::msg::BaseStatus *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _BaseStatus__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<base_demo_cpp::msg::BaseStatus *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _BaseStatus__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const base_demo_cpp::msg::BaseStatus *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _BaseStatus__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_BaseStatus(full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}

static message_type_support_callbacks_t _BaseStatus__callbacks = {
  "base_demo_cpp::msg",
  "BaseStatus",
  _BaseStatus__cdr_serialize,
  _BaseStatus__cdr_deserialize,
  _BaseStatus__get_serialized_size,
  _BaseStatus__max_serialized_size,
  nullptr
};

static rosidl_message_type_support_t _BaseStatus__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_BaseStatus__callbacks,
  get_message_typesupport_handle_function,
  &base_demo_cpp__msg__BaseStatus__get_type_hash,
  &base_demo_cpp__msg__BaseStatus__get_type_description,
  &base_demo_cpp__msg__BaseStatus__get_type_description_sources,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace base_demo_cpp

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_base_demo_cpp
const rosidl_message_type_support_t *
get_message_type_support_handle<base_demo_cpp::msg::BaseStatus>()
{
  return &base_demo_cpp::msg::typesupport_fastrtps_cpp::_BaseStatus__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, base_demo_cpp, msg, BaseStatus)() {
  return &base_demo_cpp::msg::typesupport_fastrtps_cpp::_BaseStatus__handle;
}

#ifdef __cplusplus
}
#endif
