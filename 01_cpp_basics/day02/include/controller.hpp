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

    void setDesiredPositions(
        const std::vector<double>& positions
    );

    RobotCommand computeCommand(
        const RobotState& state
    );

private:
    double kp_;
    double kd_;

    std::vector<double> desired_positions_;
};