#include "controller.hpp"
#include "robot.hpp"

#include <chrono>
#include <iostream>
#include <thread>

int main()
{
    Robot robot;

    Controller controller(
        0.5,   // Kp
        0.1    // Kd
    );

    const double dt = 0.02;

    for (int step = 0;
         step < 200;
         ++step)
    {
        RobotState state =
            robot.getState();

        RobotCommand command =
            controller.computeCommand(state);

        robot.setCommand(command);

        robot.update(dt);

        RobotState new_state =
            robot.getState();

        std::cout
            << "Step "
            << step
            << " | Left hip = "
            << new_state.positions[0]
            << " rad"
            << " | velocity = "
            << new_state.velocities[0]
            << " rad/s"
            << std::endl;

        std::this_thread::sleep_for(
            std::chrono::milliseconds(20)
        );
    }

    return 0;
}