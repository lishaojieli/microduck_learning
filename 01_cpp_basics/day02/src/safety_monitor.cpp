#include "safety_monitor.hpp"

#include <cmath>


SafetyMonitor::SafetyMonitor(
    double max_joint_velocity,
    double max_pitch
)
    : max_joint_velocity_(max_joint_velocity),
      max_pitch_(max_pitch)
{
}

SafetyState SafetyMonitor::check(
    const RobotState& state
) const
{
    for (double velocity : state.velocities)
    {
        if (std::abs(velocity) >
            max_joint_velocity_)
        {
            return SafetyState::JointVelocityFault;
        }
    }

    if (std::abs(state.imu.pitch) >
        max_pitch_)
    {
        return SafetyState::TiltFault;
    }

    return SafetyState::Safe;
}