#include "robot.hpp"

#include <iostream>

Robot::Robot()
{
    // 左腿
    servos_.emplace_back(1, -1.0, 1.0, 1.0);
    servos_.emplace_back(2, -1.5, 0.0, 1.0);
    servos_.emplace_back(3, -0.8, 0.8, 1.0);

    // 右腿
    servos_.emplace_back(4, -1.0, 1.0, 1.0);
    servos_.emplace_back(5, -1.5, 0.0, 1.0);
    servos_.emplace_back(6, -0.8, 0.8, 1.0);
}

void Robot::setJointTarget(
    Joint joint,
    double target_position
)
{
    int index = static_cast<int>(joint);

    if (index < 0 || index >= static_cast<int>(servos_.size()))
    {
        std::cout << "Invalid joint index!" << std::endl;
        return;
    }

    servos_[index].setTargetPosition(target_position);
}

double Robot::getJointPosition(Joint joint) const
{
    int index = static_cast<int>(joint);

    if (index < 0 || index >= static_cast<int>(servos_.size()))
    {
        std::cout << "Invalid joint index!" << std::endl;
        return 0.0;
    }

    return servos_[index].getCurrentPosition();
}

void Robot::update(double dt)
{
    for (Servo& servo : servos_)
    {
        servo.update(dt);
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

RobotState Robot::getState() const
{
    RobotState state;

    for (const Servo& servo : servos_)
    {
        state.positions.push_back(
            servo.getCurrentPosition()
        );

        state.velocities.push_back(
            servo.getCurrentVelocity()
        );
    }

    return state;
}