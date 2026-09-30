## 运行效果展示
<img width="496" height="272" alt="VID_20260930_124537" src="https://github.com/user-attachments/assets/41a4762b-46b2-4521-9c46-a835283d814d" />

## rviz模型
<img width="4096" height="3072" alt="IMG_20260930_121330" src="https://github.com/user-attachments/assets/3663f74b-ffb1-4151-860f-febbf19e3c8c" />
<img width="4096" height="3072" alt="IMG_20260930_121346" src="https://github.com/user-attachments/assets/cffe1cd7-2b86-48c4-999f-19879a30105c" />
<img width="4096" height="3072" alt="IMG_20260930_121339" src="https://github.com/user-attachments/assets/a2bc2a4a-9c5a-4c8c-b8c1-c8238998bced" />

## 终端结果显示
<img width="4096" height="3072" alt="IMG_20260930_121209" src="https://github.com/user-attachments/assets/9a0cfe53-204e-40f8-8dfe-070bf4ac89b8" />

# 基于ROS2与UR5的机械臂控制仿真

##  项目简介
基于 Ubuntu 22.04 与 ROS2 Humble，使用 C++ 独立开发的六轴工业机械臂（UR5）关节空间平滑控制仿真系统。实现了底层话题通信、P控制算法到RViz可视化的完整闭环。

## 技术栈
C++ / Linux (Ubuntu 22.04) / ROS2 Humble / CMake / URDF / RViz2

## 核心功能
1. 使用C++编写发布者与订阅者节点，通过 `/joint_command` 与 `/joint_states` 话题进行控制。
2. 在订阅者节点中引入P控制（Kp=0.1），实现关节平滑逼近目标，避免运动冲击。
3. 集成UR5工业URDF模型，通过 `robot_state_publisher` 发布TF坐标变换并在RViz中可视化。
4. 使用CMake构建工程，Launch文件实现一键启动，解决QoS等工程问题。

## 编译与运行
```bash
colcon build
source install/setup.bash
ros2 launch test_cpp_pkg arm_display.launch.py
