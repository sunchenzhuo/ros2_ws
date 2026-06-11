// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from base_demo_cpp:msg/BaseStatus.idl
// generated code does not contain a copyright notice
#include "base_demo_cpp/msg/detail/base_status__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `err`
#include "rosidl_runtime_c/string_functions.h"

bool
base_demo_cpp__msg__BaseStatus__init(base_demo_cpp__msg__BaseStatus * msg)
{
  if (!msg) {
    return false;
  }
  // seq
  // vx
  // vy
  // wz
  // battery_voltage
  // err
  if (!rosidl_runtime_c__String__init(&msg->err)) {
    base_demo_cpp__msg__BaseStatus__fini(msg);
    return false;
  }
  // cmd_timeout
  return true;
}

void
base_demo_cpp__msg__BaseStatus__fini(base_demo_cpp__msg__BaseStatus * msg)
{
  if (!msg) {
    return;
  }
  // seq
  // vx
  // vy
  // wz
  // battery_voltage
  // err
  rosidl_runtime_c__String__fini(&msg->err);
  // cmd_timeout
}

bool
base_demo_cpp__msg__BaseStatus__are_equal(const base_demo_cpp__msg__BaseStatus * lhs, const base_demo_cpp__msg__BaseStatus * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // seq
  if (lhs->seq != rhs->seq) {
    return false;
  }
  // vx
  if (lhs->vx != rhs->vx) {
    return false;
  }
  // vy
  if (lhs->vy != rhs->vy) {
    return false;
  }
  // wz
  if (lhs->wz != rhs->wz) {
    return false;
  }
  // battery_voltage
  if (lhs->battery_voltage != rhs->battery_voltage) {
    return false;
  }
  // err
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->err), &(rhs->err)))
  {
    return false;
  }
  // cmd_timeout
  if (lhs->cmd_timeout != rhs->cmd_timeout) {
    return false;
  }
  return true;
}

bool
base_demo_cpp__msg__BaseStatus__copy(
  const base_demo_cpp__msg__BaseStatus * input,
  base_demo_cpp__msg__BaseStatus * output)
{
  if (!input || !output) {
    return false;
  }
  // seq
  output->seq = input->seq;
  // vx
  output->vx = input->vx;
  // vy
  output->vy = input->vy;
  // wz
  output->wz = input->wz;
  // battery_voltage
  output->battery_voltage = input->battery_voltage;
  // err
  if (!rosidl_runtime_c__String__copy(
      &(input->err), &(output->err)))
  {
    return false;
  }
  // cmd_timeout
  output->cmd_timeout = input->cmd_timeout;
  return true;
}

base_demo_cpp__msg__BaseStatus *
base_demo_cpp__msg__BaseStatus__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  base_demo_cpp__msg__BaseStatus * msg = (base_demo_cpp__msg__BaseStatus *)allocator.allocate(sizeof(base_demo_cpp__msg__BaseStatus), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(base_demo_cpp__msg__BaseStatus));
  bool success = base_demo_cpp__msg__BaseStatus__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
base_demo_cpp__msg__BaseStatus__destroy(base_demo_cpp__msg__BaseStatus * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    base_demo_cpp__msg__BaseStatus__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
base_demo_cpp__msg__BaseStatus__Sequence__init(base_demo_cpp__msg__BaseStatus__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  base_demo_cpp__msg__BaseStatus * data = NULL;

  if (size) {
    data = (base_demo_cpp__msg__BaseStatus *)allocator.zero_allocate(size, sizeof(base_demo_cpp__msg__BaseStatus), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = base_demo_cpp__msg__BaseStatus__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        base_demo_cpp__msg__BaseStatus__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
base_demo_cpp__msg__BaseStatus__Sequence__fini(base_demo_cpp__msg__BaseStatus__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      base_demo_cpp__msg__BaseStatus__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

base_demo_cpp__msg__BaseStatus__Sequence *
base_demo_cpp__msg__BaseStatus__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  base_demo_cpp__msg__BaseStatus__Sequence * array = (base_demo_cpp__msg__BaseStatus__Sequence *)allocator.allocate(sizeof(base_demo_cpp__msg__BaseStatus__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = base_demo_cpp__msg__BaseStatus__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
base_demo_cpp__msg__BaseStatus__Sequence__destroy(base_demo_cpp__msg__BaseStatus__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    base_demo_cpp__msg__BaseStatus__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
base_demo_cpp__msg__BaseStatus__Sequence__are_equal(const base_demo_cpp__msg__BaseStatus__Sequence * lhs, const base_demo_cpp__msg__BaseStatus__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!base_demo_cpp__msg__BaseStatus__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
base_demo_cpp__msg__BaseStatus__Sequence__copy(
  const base_demo_cpp__msg__BaseStatus__Sequence * input,
  base_demo_cpp__msg__BaseStatus__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(base_demo_cpp__msg__BaseStatus);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    base_demo_cpp__msg__BaseStatus * data =
      (base_demo_cpp__msg__BaseStatus *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!base_demo_cpp__msg__BaseStatus__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          base_demo_cpp__msg__BaseStatus__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!base_demo_cpp__msg__BaseStatus__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
