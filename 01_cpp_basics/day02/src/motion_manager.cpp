#include "motion_manager.hpp"

MotionManager::MotionManager()
    : state_(MotionState::Standing),
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
      desired_positions_(standing_pose_)
{
}

void MotionManager::update(double time)
{
    if (time < 2.0)
    {
        state_ =
            MotionState::Standing;

        desired_positions_ =
            standing_pose_;
    }
    else if (time < 4.0)
    {
        state_ =
            MotionState::Squatting;

        desired_positions_ =
            squat_pose_;
    }
    else
    {
        state_ =
            MotionState::Standing;

        desired_positions_ =
            standing_pose_;
    }
}

const std::vector<double>&
MotionManager::getDesiredPositions() const
{
    return desired_positions_;
}

MotionState MotionManager::getState() const
{
    return state_;
}