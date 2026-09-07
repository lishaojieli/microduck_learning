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
        double max_pitch,
        double reset_max_joint_velocity
    );

    SafetyState check(
        const RobotState& state
    );

    bool canReset(
        const RobotState& state
    ) const;

    bool reset(
        const RobotState& state
    );

    SafetyState getState() const;

private:
    double max_joint_velocity_;
    double max_pitch_;
    double reset_max_joint_velocity_;


    SafetyState fault_state_;
};