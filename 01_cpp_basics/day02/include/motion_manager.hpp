#pragma once

#include "robot.hpp"

#include <vector>

enum class MotionState
{
    Idle,
    Standing,
    Squatting
};

class MotionManager
{
    public:
        MotionManager();

        void update(const RobotState& state);

        const std::vector<double>& getDesiredPositions() const;

        MotionState getState() const;

    private:
        bool isPoseReached(
            const RobotState& state,
            const std::vector<double>& target
        ) const;

        MotionState state_;

        std::vector<double> idle_pose_;
        std::vector<double> standing_pose_;
        std::vector<double> squat_pose_;

        std::vector<double> desired_positions_;

        double position_tolerance_;
};