// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from base_demo_cpp:msg/BaseStatus.idl
// generated code does not contain a copyright notice

#include "base_demo_cpp/msg/detail/base_status__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_base_demo_cpp
const rosidl_type_hash_t *
base_demo_cpp__msg__BaseStatus__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x8d, 0x8a, 0x51, 0xdb, 0x7f, 0x8d, 0xbd, 0x2c,
      0x3a, 0x67, 0x5c, 0xdc, 0xbd, 0x6b, 0x03, 0x39,
      0x9e, 0x10, 0x64, 0x7a, 0x71, 0xab, 0x6f, 0x6a,
      0x4a, 0x65, 0x27, 0x43, 0x7a, 0x5d, 0xaa, 0xfb,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char base_demo_cpp__msg__BaseStatus__TYPE_NAME[] = "base_demo_cpp/msg/BaseStatus";

// Define type names, field names, and default values
static char base_demo_cpp__msg__BaseStatus__FIELD_NAME__seq[] = "seq";
static char base_demo_cpp__msg__BaseStatus__FIELD_NAME__vx[] = "vx";
static char base_demo_cpp__msg__BaseStatus__FIELD_NAME__vy[] = "vy";
static char base_demo_cpp__msg__BaseStatus__FIELD_NAME__wz[] = "wz";
static char base_demo_cpp__msg__BaseStatus__FIELD_NAME__battery_voltage[] = "battery_voltage";
static char base_demo_cpp__msg__BaseStatus__FIELD_NAME__err[] = "err";
static char base_demo_cpp__msg__BaseStatus__FIELD_NAME__cmd_timeout[] = "cmd_timeout";

static rosidl_runtime_c__type_description__Field base_demo_cpp__msg__BaseStatus__FIELDS[] = {
  {
    {base_demo_cpp__msg__BaseStatus__FIELD_NAME__seq, 3, 3},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {base_demo_cpp__msg__BaseStatus__FIELD_NAME__vx, 2, 2},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {base_demo_cpp__msg__BaseStatus__FIELD_NAME__vy, 2, 2},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {base_demo_cpp__msg__BaseStatus__FIELD_NAME__wz, 2, 2},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {base_demo_cpp__msg__BaseStatus__FIELD_NAME__battery_voltage, 15, 15},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {base_demo_cpp__msg__BaseStatus__FIELD_NAME__err, 3, 3},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {base_demo_cpp__msg__BaseStatus__FIELD_NAME__cmd_timeout, 11, 11},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
base_demo_cpp__msg__BaseStatus__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {base_demo_cpp__msg__BaseStatus__TYPE_NAME, 28, 28},
      {base_demo_cpp__msg__BaseStatus__FIELDS, 7, 7},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "int32 seq\n"
  "float64 vx\n"
  "float64 vy\n"
  "float64 wz\n"
  "float64 battery_voltage\n"
  "string err\n"
  "bool cmd_timeout";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
base_demo_cpp__msg__BaseStatus__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {base_demo_cpp__msg__BaseStatus__TYPE_NAME, 28, 28},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 94, 94},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
base_demo_cpp__msg__BaseStatus__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *base_demo_cpp__msg__BaseStatus__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
