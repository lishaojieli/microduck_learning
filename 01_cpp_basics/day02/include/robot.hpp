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

struct ImuState
{
    double roll;
    double pitch;
    double yaw;

    double angular_velocity_x;
    double angular_velocity_y;
    double angular_velocity_z;
};

struct RobotState
{
    std::vector<double> positions;
    std::vector<double> velocities;

    ImuState imu;
};

struct RobotCommand
{
    std::vector<double> joint_targets;
};

class Robot
{
public:
    Robot();

    void setCommand(const RobotCommand& command);

    void update(double dt);

    RobotState getState() const;

    void printState() const;

private:
    std::vector<Servo> servos_;
    ImuState imu_;
};