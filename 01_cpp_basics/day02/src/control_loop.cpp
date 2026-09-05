#pragma once

#include "control_loop.hpp"
#include "controller.hpp"
#include "motion_manager.hpp"
#include "robot.hpp"

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
      previous_time_(std::chrono::steady_clock::now())
{
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

void ControlLoop::step()
{
    auto loop_start = std::chrono::steady_clock::now();

    double dt = std::chrono::duration<double> (loop_start - previous_time_).count();

    previous_time_ = loop_start;

    RobotState state = robot_.getState();

    motion_manager_.update(state);

    controller_.setDesiredPositions(motion_manager_.getDesiredPositions());

    RobotCommand command = controller_.computeCommand(state);

    robot_.setCommand(command);

    robot_.update(dt);

    std::cout
        << "Motion state: "
        << motionStateToString(motion_manager_.getState())
        << std::endl;

    auto loop_end = std::chrono::steady_clock::now();

    double computation_time = std::chrono::duration<double> (loop_end - loop_start).count();

    double sleep_time = period_seconds_ - computation_time;

    if (sleep_time > 0.0)
    {
        std::this_thread::sleep_for(std::chrono::duration<double> (sleep_time));
    }
    else
    {
        std::cout
            << "Warning: control loop overrun!"
            << std::endl;
    }
}

