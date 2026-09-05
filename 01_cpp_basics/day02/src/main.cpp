#include "control_loop.hpp"
#include "controller.hpp"
#include "motion_manager.hpp"
#include "robot.hpp"

int main()
{
    Robot robot;

    Controller controller(
        0.1,
        0.0
    );

    MotionManager motion_manager;

    ControlLoop loop(
        robot,
        controller,
        motion_manager,
        50.0
    );

    motion_manager.setCommand(
        MotionCommand::Stand
    );

    for (int i = 0; i < 150; ++i)
    {
        loop.step();
    }

    motion_manager.setCommand(
        MotionCommand::Squat
    );

    for (int i = 0; i < 150; ++i)
    {
        loop.step();
    }

    motion_manager.setCommand(
        MotionCommand::Stand
    );

    for (int i = 0; i < 150; ++i)
    {
        loop.step();
    }

    return 0;
}