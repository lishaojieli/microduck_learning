#include "robot.hpp"

#include <iostream>

Robot::Robot()
{
    // 左腿
    servos_.emplace_back(1, -1.0, 1.0);
    servos_.emplace_back(2, -1.5, 0.0);
    servos_.emplace_back(3, -0.8, 0.8);

    // 右腿
    servos_.emplace_back(4, -1.0, 1.0);
    servos_.emplace_back(5, -1.5, 0.0);
    servos_.emplace_back(6, -0.8, 0.8);
}

void Robot::setJointTarget(
    int joint_index,
    double target_position
)
{
    servos_[joint_index].setTargetPosition(target_position);
}

void Robot::update()
{
    for (Servo& servo : servos_)
    {
        servo.update();
    }
}

void Robot::printState() const
{
    for (const Servo& servo : servos_)
    {
        servo.printState();

        std::cout << std::endl;
    }
}