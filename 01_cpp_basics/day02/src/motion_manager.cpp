#include "motion_manager.hpp"

#include <cmath>

MotionManager::MotionManager()
    : state_(MotionState::Idle),
      command_(MotionCommand::None),
      idle_pose_
      {
          0.0,
          0.0,
          0.0,
          0.0,
          0.0,
          0.0
      },
      standing_pose_
      {
          0.3,
          -0.6,
          0.3,
          -0.3,
          -0.6,
          -0.3
      },
      squat_pose_
      {
          0.5,
          -1.2,
          0.5,
          -0.5,
          -1.2,
          -0.5
      },
      desired_positions_(idle_pose_),
      position_tolerance_(0.02)
{
}

void MotionManager::setCommand(MotionCommand command)
{
    command_ = command;
}

bool MotionManager::isPoseReached(
    const RobotState& state,
    const std::vector<double>& target
) const
{
    if (state.positions.size() != target.size())
    {
        return false;
    }

    for (std::size_t i = 0;
         i < target.size();
         ++i)
    {
        double error =
            target[i] - state.positions[i];

        if (std::abs(error) >
            position_tolerance_)
        {
            return false;
        }
    }

    return true;
}

void MotionManager::update(const RobotState& state)
{
    switch (command_)
    {
        case MotionCommand::None:
            break;

        case MotionCommand::Stand:

            desired_positions_ = standing_pose_;

            if (isPoseReached(state, standing_pose_))
            {
                state_ = MotionState::Standing;
            }
            else
            {
                state_ = MotionState::MovingToStanding;
            }

            break;

        case MotionCommand::Squat:

            desired_positions_ = squat_pose_;

            if (isPoseReached(state, squat_pose_))
            {
                state_ = MotionState::Squatting;
            }
            else
            {
                state_ = MotionState::MovingToSquat;
            }

            break;
    }
}

const std::vector<double>& MotionManager::getDesiredPositions() const
{
    return desired_positions_;
}

MotionState MotionManager::getState() const
{
    return state_;
}