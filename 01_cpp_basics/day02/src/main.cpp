#include "robot.hpp"

#include <chrono>
#include <iostream>
#include <thread>

int main()
{
    Robot robot;

    robot.setJointTarget(
        Joint::LeftHip,
        0.8
    );

    robot.setJointTarget(
        Joint::RightHip,
        0.6
    );

    const double dt = 0.02;

    for (int i = 0; i < 100; ++i)
    {
        robot.update(dt);

        RobotState state =
            robot.getState();

        std::cout
            << "Step: "
            << i
            << std::endl;

        std::cout
            << "Left hip: "
            << state.positions[
                   static_cast<int>(
                       Joint::LeftHip
                   )
               ]
            << " rad"
            << std::endl;

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