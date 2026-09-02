#pragma once

#include "servo.hpp"

#include <vector>

class Robot
{
public:
    Robot();

    void setJointTarget(
        int joint_index,
        double target_position
    );

    void update();

    void printState() const;

private:
    std::vector<Servo> servos_;
};