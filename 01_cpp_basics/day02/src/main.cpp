#include "robot.hpp"

int main()
{
    Robot robot;

    robot.setJointTarget(0, 0.3);
    robot.setJointTarget(1, -0.6);
    robot.setJointTarget(2, 0.3);

    robot.setJointTarget(3, -0.3);
    robot.setJointTarget(4, -0.6);
    robot.setJointTarget(5, -0.3);

    robot.update();

    robot.printState();

    return 0;
}