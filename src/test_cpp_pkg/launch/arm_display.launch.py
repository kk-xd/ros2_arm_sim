from launch import LaunchDescription
from launch_ros.actions import Node
from launch.substitutions import Command, FindExecutable, PathJoinSubstitution
from launch_ros.substitutions import FindPackageShare

def generate_launch_description():
    robot_description_content = Command([
        PathJoinSubstitution([FindExecutable(name="xacro")]), " ",
        PathJoinSubstitution([FindPackageShare("ur_description"), "urdf", "ur.urdf.xacro"]), " ",
        "ur_type:=ur5e", " ", "name:=ur",
    ])
    return LaunchDescription([
        Node(package="robot_state_publisher", executable="robot_state_publisher", parameters=[{"robot_description": robot_description_content}]),
        Node(package="test_cpp_pkg", executable="joint_subscriber", name="virtual_arm"),
        Node(package="rviz2", executable="rviz2", name="rviz2", arguments=["-f", "base_link"]),
    ])