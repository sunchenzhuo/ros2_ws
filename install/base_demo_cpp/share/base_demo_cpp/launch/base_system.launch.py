'''
Author: 树 shuxianshengio@126.com
Date: 2026-06-09 15:26:09
LastEditors: 树 shuxianshengio@126.com
LastEditTime: 2026-06-10 14:13:48
FilePath: /shu/ros2_ws/src/base_demo_cpp/launch/base_system.launch.py
Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE)
'''
from launch import LaunchContext, LaunchDescription
from launch_ros.actions import Node
from launch.substitutions import LaunchConfiguration
from launch.actions import DeclareLaunchArgument

def generate_launch_description():
    cmd_timeout_ms_args=DeclareLaunchArgument(
        'cmd_timeout_ms',
        default_value='2000',
        description='Timeout in milliseconds for /cmd_vel'
    )
    test_vx_arg=DeclareLaunchArgument(
        'test_vx',
        default_value='0.30',
        description='Test cmd_vel linear x'
    )

    test_vy_arg=DeclareLaunchArgument(
        'test_vy',
        default_value='0.00',
        description='Test cmd_vel linear y'
    )

    test_wz_arg=DeclareLaunchArgument(
        'test_wz',
        default_value='0.50',
        description='Test cmd_vel angualr z'
    )

    publish_period_ms_arg=DeclareLaunchArgument(
        'publish_period_ms',
        default_value='200',
        description='Publish period in milliseconds for cmd_vel_test_node'
    )
    cmd_timeout_ms=LaunchConfiguration('cmd_timeout_ms')
    test_vx=LaunchConfiguration("test_vx")
    test_vy=LaunchConfiguration("test_vy")
    test_wz=LaunchConfiguration("test_wz")
    publish_period_ms=LaunchConfiguration("publish_period_ms")
    base_node=Node(
        package='base_demo_cpp',
        executable='base_node',
        name='base_node',
        output='screen',
        parameters=[
            {'cmd_timeout_ms':cmd_timeout_ms,
             "server_ip":"127.0.0.1",
             "server_port":17000}
        ]
        )

    status_listener_node=Node(
        package='base_demo_cpp',
        executable='base_status_listener_node',
        name='base_status_listener_node',
        output='screen'
    )

    cmd_vel_test_node=Node(
        package='base_demo_cpp',
        executable='cmd_vel_test_node',
        name='cmd_vel_test_node',
        output='screen',
        parameters=[
            {
                'test_vx':test_vx,
                'test_vy':test_vy,
                'test_wz':test_wz,
                'publish_period_ms':publish_period_ms,
            }
        ]
    )

    return LaunchDescription([
        cmd_timeout_ms_args,
        test_vx_arg,
        test_vy_arg,
        test_wz_arg,
        publish_period_ms_arg,
        base_node,
        status_listener_node,
        cmd_vel_test_node,
    ])