#pragma once

#include <vector>

enum class MotionState
{
    Standing,
    Squatting
};

class MotionManager
{
public:
    MotionManager();

    void update(double time);

    const std::vector<double>& getDesiredPositions() const;

    MotionState getState() const;

private:
    MotionState state_;

    std::vector<double> standing_pose_;
    std::vector<double> squat_pose_;

    std::vector<double> desired_positions_;
};