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
    cmd_timeout_ms=LaunchConfiguration('cmd_timeout_ms')
    base_node=Node(
        package='base_demo_cpp',
        executable='base_node',
        name='base_node',
        output='screen',
        parameters=[
            {'cmd_timeout_ms':cmd_timeout_ms}
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
        output='screen'
    )

    return LaunchDescription([
        cmd_timeout_ms_args,
        base_node,
        status_listener_node,
        cmd_vel_test_node,
    ])