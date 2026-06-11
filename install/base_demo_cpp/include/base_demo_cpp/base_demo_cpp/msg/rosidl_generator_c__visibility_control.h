// generated from rosidl_generator_c/resource/rosidl_generator_c__visibility_control.h.in
// generated code does not contain a copyright notice

#ifndef BASE_DEMO_CPP__MSG__ROSIDL_GENERATOR_C__VISIBILITY_CONTROL_H_
#define BASE_DEMO_CPP__MSG__ROSIDL_GENERATOR_C__VISIBILITY_CONTROL_H_

#ifdef __cplusplus
extern "C"
{
#endif

// This logic was borrowed (then namespaced) from the examples on the gcc wiki:
//     https://gcc.gnu.org/wiki/Visibility

#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define ROSIDL_GENERATOR_C_EXPORT_base_demo_cpp __attribute__ ((dllexport))
    #define ROSIDL_GENERATOR_C_IMPORT_base_demo_cpp __attribute__ ((dllimport))
  #else
    #define ROSIDL_GENERATOR_C_EXPORT_base_demo_cpp __declspec(dllexport)
    #define ROSIDL_GENERATOR_C_IMPORT_base_demo_cpp __declspec(dllimport)
  #endif
  #ifdef ROSIDL_GENERATOR_C_BUILDING_DLL_base_demo_cpp
    #define ROSIDL_GENERATOR_C_PUBLIC_base_demo_cpp ROSIDL_GENERATOR_C_EXPORT_base_demo_cpp
  #else
    #define ROSIDL_GENERATOR_C_PUBLIC_base_demo_cpp ROSIDL_GENERATOR_C_IMPORT_base_demo_cpp
  #endif
#else
  #define ROSIDL_GENERATOR_C_EXPORT_base_demo_cpp __attribute__ ((visibility("default")))
  #define ROSIDL_GENERATOR_C_IMPORT_base_demo_cpp
  #if __GNUC__ >= 4
    #define ROSIDL_GENERATOR_C_PUBLIC_base_demo_cpp __attribute__ ((visibility("default")))
  #else
    #define ROSIDL_GENERATOR_C_PUBLIC_base_demo_cpp
  #endif
#endif

#ifdef __cplusplus
}
#endif

#endif  // BASE_DEMO_CPP__MSG__ROSIDL_GENERATOR_C__VISIBILITY_CONTROL_H_
