#pragma once

#include "controller.hpp"
#include "motion_manager.hpp"
#include "robot.hpp"

#include <chrono>

class ControlLoop
{
    public:
        ControlLoop(
            Robot& robot,
            Controller& controller,
            MotionManager& motion_manager,
            double frequency_hz
        );

        void step();

    private:
        Robot& robot_;
        Controller& controller_;
        MotionManager& motion_manager_;

        double frequency_hz_;
        double period_seconds_;

        std::chrono::steady_clock::time_point previous_time_;
};