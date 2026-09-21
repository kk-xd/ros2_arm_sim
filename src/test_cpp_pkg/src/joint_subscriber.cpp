#include <memory>
#include <vector>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"
#include "sensor_msgs/msg/joint_state.hpp" // RViz需要的类型

class VirtualArm : public rclcpp::Node {
public:
    VirtualArm() : Node("virtual_arm") {
        state_publisher_ = this->create_publisher<sensor_msgs::msg::JointState>("/joint_state", 10);
        subscription_ = this->create_subscription<std_msgs::msg::Float64MultiArray>(
            "/joint_command", 10,
            [this](const std_msgs::msg::Float64MultiArray::SharedPtr msg) {
                // 平滑运动逻辑（比例控制）
                for (size_t i = 0; i < msg->data.size() && i < current_positions_.size(); ++i) {
                    current_positions_[i] += (msg->data[i] - current_positions_[i]) * 0.1;
                }
                auto state_msg = sensor_msgs::msg::JointState();
                state_msg.header.stamp = this->now();
                // UR5 关节名字，一字不差！
                state_msg.name = {"shoulder_pan_joint", "shoulder_lift_joint", "elbow_joint", 
                                  "wrist_1_joint", "wrist_2_joint", "wrist_3_joint"};
                state_msg.position = current_positions_;
                state_publisher_->publish(state_msg);
            }
        );
    }
private:
    rclcpp::Publisher<sensor_msgs::msg::JointState>::SharedPtr state_publisher_;
    rclcpp::Subscription<std_msgs::msg::Float64MultiArray>::SharedPtr subscription_;
    std::vector<double> current_positions_ = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0}; 
};

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<VirtualArm>());
    rclcpp::shutdown();
    return 0;
}