# 基于ROS2与UR5的机械臂控制仿真

## 项目简介
基于 Ubuntu 22.04 与 ROS2 Humble，使用 C++ 独立开发的六轴工业机械臂（UR5）关节空间平滑控制仿真系统。本项目实现了从底层节点通信、运动控制算法到上层可视化展示的完整闭环，验证了ROS2分布式通信与C++工程化开发能力。

## 技术栈
- **编程语言**：C++（面向对象、Lambda表达式、智能指针）
- **操作系统**：Linux（Ubuntu 22.04）
- **机器人框架**：ROS2 Humble（话题通信、Launch文件、TF坐标变换）
- **构建工具**：CMake / Colcon
- **可视化**：URDF、RViz2

## 核心功能
1. **多节点话题通信**：使用C++编写发布者（`joint_publisher`）与订阅者（`joint_subscriber`）节点，通过 `/joint_command` 与 `/joint_state` 话题实现控制指令下发与关节状态反馈。
2. **平滑运动控制**：在订阅者节点中引入比例控制（P控制）算法，实现关节平滑逼近目标角度。
3. **UR5模型集成**：集成工业级UR5机械臂URDF模型，通过 `robot_state_publisher` 发布TF坐标变换。
4. **工程化构建**：编写Launch文件实现一键启动多个节点，并解决CMake依赖配置与RViz QoS（Durability Policy）不匹配等工程问题。

## 编译与运行
```bash
# 1. 编译工作空间
colcon build
source install/setup.bash

# 2. 启动机器人模型与RViz
ros2 launch test_cpp_pkg arm_display.launch.py

# 3. 在另一个终端启动指令发布者
source install/setup.bash
ros2 run test_cpp_pkg joint_publisher
