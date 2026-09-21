from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    
    return LaunchDescription([
        Node(
            package='test_cpp_pkg',
            executable='joint_publisher',
            name='joint_publisher'
            ),
        
        Node(
            package='test_cpp_pkg',
            executable='joint_subscriber',
            name='virtual_arm'
            ),
    ])
    