#include "robot.hpp"

#include <chrono>
#include <iostream>
#include <thread>

int main()
{
    Robot robot;

    robot.setJointTarget(Joint::LeftHip, 0.8);
    robot.setJointTarget(Joint::LeftKnee, -1.0);
    robot.setJointTarget(Joint::LeftAnkle, 0.4);

    const double dt = 0.02;

    for (int i = 0; i < 100; ++i)
    {
        robot.update(dt);

        double hip =
            robot.getJointPosition(Joint::LeftHip);

        std::cout
            << "Step " << i
            << " | Left hip: "
            << hip
            << " rad"
            << std::endl;

        std::this_thread::sleep_for(
            std::chrono::milliseconds(20)
        );
    }

    return 0;
}