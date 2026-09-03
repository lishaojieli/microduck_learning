#include "robot.hpp"

#include <chrono>
#include <iostream>
#include <thread>

int main()
{
    Robot robot;

    RobotCommand command;

    command.joint_targets =
    {
        0.3,
        -0.6,
        0.3,
        -0.3,
        -0.6,
        -0.3
    };

    robot.setCommand(command);

    const double dt = 0.02;

    for (int i = 0; i < 100; ++i)
    {
        robot.update(dt);

        RobotState state =
            robot.getState();

        std::cout
            << "Step "
            << i
            << std::endl;

        for (std::size_t j = 0;
             j < state.positions.size();
             ++j)
        {
            std::cout
                << "Joint "
                << j
                << ": "
                << state.positions[j]
                << " rad"
                << std::endl;
        }

        std::cout
            << "Pitch: "
            << state.imu.pitch
            << " rad"
            << std::endl;

        std::cout << std::endl;

        std::this_thread::sleep_for(
            std::chrono::milliseconds(20)
        );
    }

    return 0;
}