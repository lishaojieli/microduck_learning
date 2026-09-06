#pragma once

#include "control_loop.hpp"
#include "controller.hpp"
#include "motion_manager.hpp"
#include "robot.hpp"

#include <chrono>
#include <iostream>
#include <thread>

#include "control_loop.hpp"

#include <chrono>
#include <iostream>
#include <thread>

ControlLoop::ControlLoop(
    Robot& robot,
    Controller& controller,
    MotionManager& motion_manager,
    double frequency_hz
)
    : robot_(robot),
      controller_(controller),
      motion_manager_(motion_manager),
      frequency_hz_(frequency_hz),
      period_seconds_(1.0 / frequency_hz),
      running_(false)
{
}

void ControlLoop::stop()
{
    running_ = false;
}



const char* motionStateToString(MotionState state)
{
    switch (state)
    {
        case MotionState::Idle:
            return "Idle";

        case MotionState::Standing:
        return "Standing";

        case MotionState::MovingToStanding:
            return "MovingToStanding";

        case MotionState::MovingToSquat:
            return "MovingToSquat";

        case MotionState::Squatting:
            return "Squatting";
    }

    return "Unknown";
}

void ControlLoop::run()
{
    int step = 0;

    running_ = true;

    auto previous_time =
        std::chrono::steady_clock::now();

    while (running_)
    {
        auto loop_start =
            std::chrono::steady_clock::now();

        double dt =
            std::chrono::duration<double>(
                loop_start - previous_time
            ).count();

        previous_time = loop_start;

        RobotState state =
            robot_.getState();

        motion_manager_.update(state);

        controller_.setDesiredPositions(
            motion_manager_
                .getDesiredPositions()
        );

        RobotCommand command =
            controller_
                .computeCommand(state);

        robot_.setCommand(command);

        robot_.update(dt);

        auto loop_end =
            std::chrono::steady_clock::now();

        double computation_time =
            std::chrono::duration<double>(
                loop_end - loop_start
            ).count();

        double sleep_time =
            period_seconds_
            - computation_time;

        if (sleep_time > 0.0)
        {
            std::this_thread::sleep_for(
                std::chrono::duration<double>(
                    sleep_time
                )
            );
        }
        else
        {
            std::cout
                << "Warning: control loop overrun!"
                << std::endl;
        }
        if (step % 10 == 0)
        {
            std::cout
                << "Motion state: "
                << motionStateToString(
                    motion_manager_.getState()
                )
                << std::endl;
        }

        ++step;
    }
}
