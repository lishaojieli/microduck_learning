#pragma once

#include "servo.hpp"

#include <vector>

enum class Joint
{
    LeftHip = 0,
    LeftKnee,
    LeftAnkle,
    RightHip,
    RightKnee,
    RightAnkle
};

class Robot
{
public:
    Robot();

    void setJointTarget(
        Joint joint,
        double target_position
    );

    double getJointPosition(Joint joint) const;

    void update(double dt);

    void printState() const;

private:
    std::vector<Servo> servos_;
};