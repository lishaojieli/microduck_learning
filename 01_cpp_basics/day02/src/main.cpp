#include "robot.hpp"

#include <iostream>

int main()
{
    Robot robot;

    robot.setJointTarget(Joint::LeftHip, 0.3);
    robot.setJointTarget(Joint::LeftKnee, -0.6);
    robot.setJointTarget(Joint::LeftAnkle, 0.3);

    robot.update();

    double left_knee =
        robot.getJointPosition(Joint::LeftKnee);

    std::cout
        << "Left knee position: "
        << left_knee
        << " rad"
        << std::endl;

    return 0;
}