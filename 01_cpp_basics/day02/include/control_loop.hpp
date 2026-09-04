#pragma once

#include "controller.hpp"
#include "robot.hpp"

class ControlLoop
{
public:
    ControlLoop(
        Robot& robot,
        Controller& controller,
        double frequency_hz
    );

    void run();

private:
    Robot& robot_;
    Controller& controller_;

    double frequency_hz_;
    double period_seconds_;
};