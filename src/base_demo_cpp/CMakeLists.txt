cmake_minimum_required(VERSION 3.8)
project(base_demo_cpp)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# 查找 ROS2 构建系统和依赖包
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)

# 编译 talker_node 发布者节点
add_executable(talker_node src/talker_node.cpp)
ament_target_dependencies(talker_node
  rclcpp
  std_msgs
)

# 编译 listener_node 订阅者节点
add_executable(listener_node src/listener_node.cpp)
ament_target_dependencies(listener_node
  rclcpp
  std_msgs
)

add_executable(base_status_node src/base_status_node.cpp)
ament_target_dependencies(base_status_node rclcpp std_msgs)

add_executable(cmd_vel_listener_node src/cmd_vel_listener_node.cpp)
ament_target_dependencies(cmd_vel_listener_node rclcpp geometry_msgs)

add_executable(base_node src/base_node.cpp)
ament_target_dependencies(base_node rclcpp std_msgs geometry_msgs)

# 安装可执行文件到 install/base_demo_cpp/lib/base_demo_cpp/
# 这样 ros2 run base_demo_cpp talker_node / listener_node 才能找到
install(TARGETS
  talker_node
  listener_node
  base_status_node
  cmd_vel_listener_node
  base_node
  DESTINATION lib/${PROJECT_NAME}
)


if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  find_package(geometry_msgs REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()