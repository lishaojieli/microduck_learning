#pragma once

#include "robot.hpp"

#include <vector>

class Controller
{
public:
    Controller();

    RobotCommand computeCommand(
        const RobotState& state
    );

private:
    std::vector<double> target_positions_;
};