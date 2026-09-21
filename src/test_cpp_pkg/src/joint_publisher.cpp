#include <chrono>
#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"

using namespace std::chrono_literals;

class JointPublisher : public rclcpp::Node {
public:
    JointPublisher() : Node("joint_publisher") {
        publisher_ = this->create_publisher<std_msgs::msg::Float64MultiArray>("/joint_command", 10);
        timer_ = this->create_wall_timer(1s, [this]() {
            auto message = std_msgs::msg::Float64MultiArray();
            static int count = 0;
            // 6个关节，每次增加
            message.data = {count*0.1, count*0.15, count*0.2, count*0.25, count*0.3, count*0.35};
            count++;
            RCLCPP_INFO(this->get_logger(), "发布目标角度: [%.1f, %.1f, %.1f, %.1f, %.1f, %.1f]", 
                        message.data[0], message.data[1], message.data[2], message.data[3], message.data[4], message.data[5]);
            publisher_->publish(message);
        });
    }
private:
    rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<JointPublisher>());
    rclcpp::shutdown();
    return 0;
}