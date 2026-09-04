#include "controller.hpp"
#include "robot.hpp"

#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

int main()
{
    Robot robot;

    Controller controller(
        1.5,
        0.1
    );

    std::vector<double> standing_pose =
    {
        0.3,
        -0.6,
        0.3,

        -0.3,
        -0.6,
        -0.3
    };

    std::vector<double> squat_pose =
    {
        0.5,
        -1.2,
        0.5,

        -0.5,
        -1.2,
        -0.5
    };

    const double dt = 0.02;

    for (int step = 0;
         step < 300;
         ++step)
    {
        if (step == 0)
        {
            controller.setDesiredPositions(
                standing_pose
            );
        }

        if (step == 100)
        {
            controller.setDesiredPositions(
                squat_pose
            );
        }

        if (step == 200)
        {
            controller.setDesiredPositions(
                standing_pose
            );
        }

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
            << " | Left knee = "
            << new_state.positions[1]
            << std::endl;

        std::this_thread::sleep_for(
            std::chrono::milliseconds(20)
        );
    }

    return 0;
}