cmake_minimum_required(VERSION 3.8)
project(base_demo_cpp)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/BaseStatus.msg"
  DEPENDENCIES geometry_msgs
)

rosidl_get_typesupport_target(cpp_typesupport_target
  ${PROJECT_NAME}
  rosidl_typesupport_cpp
)

add_library(tcp_client STATIC
  src/tcp_client.cpp
)

target_include_directories(tcp_client PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

add_executable(base_node
  src/base_node.cpp
)

ament_target_dependencies(base_node
  rclcpp
  geometry_msgs
)

target_link_libraries(base_node
  tcp_client
  "${cpp_typesupport_target}"
)

add_executable(base_status_listener_node
  src/base_status_listener_node.cpp
)

ament_target_dependencies(base_status_listener_node
  rclcpp
)

target_link_libraries(base_status_listener_node
  "${cpp_typesupport_target}"
)

add_executable(cmd_vel_test_node
  src/cmd_vel_test_node.cpp
)

ament_target_dependencies(cmd_vel_test_node
  rclcpp
  geometry_msgs
)

add_executable(tcp_client_test_node
  src/tcp_client_test_node.cpp
)

ament_target_dependencies(tcp_client_test_node
  rclcpp
)

target_link_libraries(tcp_client_test_node
  tcp_client
)

install(TARGETS
  base_node
  base_status_listener_node
  cmd_vel_test_node
  tcp_client_test_node
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}
)

install(DIRECTORY
  include/
  DESTINATION include
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_export_dependencies(rosidl_default_runtime)

ament_package()