#include "safety_monitor.hpp"

#include <cmath>

SafetyMonitor::SafetyMonitor(
    double max_joint_velocity,
    double max_pitch
)
    : max_joint_velocity_(max_joint_velocity),
      max_pitch_(max_pitch),
      fault_state_(SafetyState::Safe)
{
}

SafetyState SafetyMonitor::check(
    const RobotState& state
)
{
    // 如果已经发生过故障，直接返回锁存故障
    if (fault_state_ != SafetyState::Safe)
    {
        return fault_state_;
    }

    for (double velocity : state.velocities)
    {
        if (std::abs(velocity) >
            max_joint_velocity_)
        {
            fault_state_ =
                SafetyState::JointVelocityFault;

            return fault_state_;
        }
    }

    if (std::abs(state.imu.pitch) >
        max_pitch_)
    {
        fault_state_ =
            SafetyState::TiltFault;

        return fault_state_;
    }

    return SafetyState::Safe;
}
void SafetyMonitor::reset()
{
    fault_state_ =
        SafetyState::Safe;
}

SafetyState SafetyMonitor::getState() const
{
    return fault_state_;
}