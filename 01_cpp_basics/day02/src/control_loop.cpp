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
      period_seconds_(1.0 / frequency_hz)
{
}

void ControlLoop::run()
{
    auto start_time =
        std::chrono::steady_clock::now();

    auto previous_time =
        start_time;

    for (int step = 0;
         step < 300;
         ++step)
    {
        auto loop_start =
            std::chrono::steady_clock::now();

        double dt = period_seconds_;

        if (step > 0)
        {
            dt =
                std::chrono::duration<double>(
                    loop_start - previous_time
                ).count();
        }

        previous_time =
            loop_start;

        double elapsed_time =
            std::chrono::duration<double>(
                loop_start - start_time
            ).count();

        // ① 更新运动状态
        motion_manager_.update(
            elapsed_time
        );

        // ② 把当前动作目标交给 Controller
        controller_.setDesiredPositions(
            motion_manager_
                .getDesiredPositions()
        );

        // ③ 读取机器人状态
        RobotState state =
            robot_.getState();

        // ④ 计算控制命令
        RobotCommand command =
            controller_
                .computeCommand(state);

        // ⑤ 下发控制命令
        robot_.setCommand(command);

        // ⑥ 更新机器人
        robot_.update(dt);

        RobotState new_state =
            robot_.getState();

        std::cout
            << "Time: "
            << elapsed_time
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