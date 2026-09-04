#include "control_loop.hpp"

#include <chrono>
#include <iostream>
#include <thread>

ControlLoop::ControlLoop(
    Robot& robot,
    Controller& controller,
    double frequency_hz
)
    : robot_(robot),
      controller_(controller),
      frequency_hz_(frequency_hz),
      period_seconds_(1.0 / frequency_hz)
{
}

void ControlLoop::run()
{
    const std::vector<double> standing_pose =
    {
        0.3,
        -0.6,
        0.3,
        -0.3,
        -0.6,
        -0.3
    };

    const std::vector<double> squat_pose =
    {
        0.5,
        -1.2,
        0.5,
        -0.5,
        -1.2,
        -0.5
    };

    controller_.setDesiredPositions(
        standing_pose
    );

    auto previous_time =
        std::chrono::steady_clock::now();

    for (int step = 0;
         step < 300;
         ++step)
    {
        auto loop_start =
            std::chrono::steady_clock::now();

        double dt =
            period_seconds_;

        if (step > 0)
        {
            dt =
                std::chrono::duration<double>(
                    loop_start - previous_time
                ).count();
        }

        previous_time =
            loop_start;

        if (step == 100)
        {
            controller_.setDesiredPositions(
                squat_pose
            );
        }

        if (step == 200)
        {
            controller_.setDesiredPositions(
                standing_pose
            );
        }

        RobotState state =
            robot_.getState();

        RobotCommand command =
            controller_.computeCommand(state);

        robot_.setCommand(command);

        robot_.update(dt);

        RobotState new_state =
            robot_.getState();

        std::cout
            << "Step: "
            << step
            << " | dt: "
            << dt
            << " | Hip: "
            << new_state.positions[0]
            << " | Knee: "
            << new_state.positions[1]
            << std::endl;

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
    }
}