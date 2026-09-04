#pragma once

#include "robot.hpp"

#include <vector>

class Controller
{
public:
    Controller(
        double kp,
        double kd
    );

    RobotCommand computeCommand(
        const RobotState& state
    );

private:
    double kp_;
    double kd_;

    std::vector<double> desired_positions_;
};