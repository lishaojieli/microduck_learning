#pragma once

#include "control_loop.hpp"
#include "controller.hpp"
#include "motion_manager.hpp"
#include "robot.hpp"
#include "safety_monitor.hpp"

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
    CommandMailbox& mailbox,
    SafetyMonitor& safety_monitor,
    double frequency_hz
)
    : robot_(robot),
      controller_(controller),
      motion_manager_(motion_manager),
      mailbox_(mailbox),
      safety_monitor_(safety_monitor),
      frequency_hz_(frequency_hz),
      period_seconds_(1.0 / frequency_hz),
      running_(false)
{
}


const char* motionStateToString(
    MotionState state
)
{
    switch (state)
    {
    case MotionState::Idle:
        return "Idle";

    case MotionState::MovingToStanding:
        return "MovingToStanding";

    case MotionState::Standing:
        return "Standing";

    case MotionState::MovingToSquat:
        return "MovingToSquat";

    case MotionState::Squatting:
        return "Squatting";

    case MotionState::Stopped:
        return "Stopped";

    case MotionState::EmergencyStopped:
        return "EMERGENCY STOPPED";
    }

    return "Unknown";
}

const char* safetyStateToString(
    SafetyState state
)
{
    switch (state)
    {
    case SafetyState::Safe:
        return "Safe";

    case SafetyState::JointPositionFault:
        return "JointPositionFault";

    case SafetyState::JointVelocityFault:
        return "JointVelocityFault";

    case SafetyState::TiltFault:
        return "TiltFault";
    }

    return "Unknown";
}

void ControlLoop::run()
{
    running_ = true;

    int step = 0;

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

        previous_time =
            loop_start;

        RobotState state =
            robot_.getState();

        MotionCommand motion_command =
            mailbox_.takeCommand();

        if (motion_command == MotionCommand::Reset)
        {
            safety_monitor_.reset();

            motion_manager_.setCommand(
                MotionCommand::Reset
            );
        }
        else
        {
            SafetyState safety_state =
                safety_monitor_.check(state);

            if (safety_state != SafetyState::Safe)
            {
                motion_manager_.setCommand(
                    MotionCommand::EmergencyStop
                );
            }
            else if (motion_command != MotionCommand::None)
            {
                motion_manager_.setCommand(
                    motion_command
                );
            }
        }

        motion_manager_.update(
            state
        );

        controller_.setDesiredPositions(
            motion_manager_
                .getDesiredPositions()
        );

        RobotCommand robot_command =
            controller_
                .computeCommand(state);

        robot_.setCommand(
            robot_command
        );

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
                << "Safety state: "
                << safetyStateToString(
                    safety_monitor_.getState()
                )
                << std::endl;
        }

        ++step;
    }
}

void ControlLoop::stop()
{
    running_ = false;
}
