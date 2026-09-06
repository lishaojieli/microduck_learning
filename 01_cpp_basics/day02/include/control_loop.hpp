#pragma once

#include "controller.hpp"
#include "motion_manager.hpp"
#include "robot.hpp"
#include "command_mailbox.hpp"

#include <atomic>
#include <chrono>

class ControlLoop
{
public:
    ControlLoop(
        Robot& robot,
        Controller& controller,
        MotionManager& motion_manager,
        CommandMailbox& mailbox,
        double frequency_hz
    );

    void run();
    void stop();

private:
    Robot& robot_;
    Controller& controller_;
    MotionManager& motion_manager_;
    CommandMailbox& mailbox_;

    double frequency_hz_;
    double period_seconds_;

    std::atomic<bool> running_;
};