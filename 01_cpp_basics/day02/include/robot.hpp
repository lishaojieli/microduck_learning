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

struct RobotState
{
    std::vector<double> positions;
    std::vector<double> velocities;
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

    RobotState getState() const;

    void printState() const;

private:
    std::vector<Servo> servos_;
};