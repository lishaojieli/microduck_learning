#pragma once

#include "robot.hpp"

enum class SafetyState
{
    Safe,
    JointPositionFault,
    JointVelocityFault,
    TiltFault
};

class SafetyMonitor
{
public:
    SafetyMonitor(
        double max_joint_velocity,
        double max_pitch
    );

    SafetyState check(
        const RobotState& state
    ) const;

private:
    double max_joint_velocity_;
    double max_pitch_;
};