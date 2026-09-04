#include "controller.hpp"
#include "robot.hpp"

#include <chrono>
#include <iostream>
#include <thread>

int main()
{
    Robot robot;
    Controller controller;

    const double dt = 0.02;

    for (int i = 0; i < 100; ++i)
    {
        RobotState state =
            robot.getState();

        RobotCommand command =
            controller.computeCommand(state);

        robot.setCommand(command);

        robot.update(dt);

        std::cout
            << "Step "
            << i
            << std::endl;

        RobotState new_state =
            robot.getState();

        for (std::size_t j = 0;
             j < new_state.positions.size();
             ++j)
        {
            std::cout
                << "Joint "
                << j
                << ": "
                << new_state.positions[j]
                << " rad"
                << std::endl;
        }

        std::cout << std::endl;

        std::this_thread::sleep_for(
            std::chrono::milliseconds(20)
        );
    }

    return 0;
}