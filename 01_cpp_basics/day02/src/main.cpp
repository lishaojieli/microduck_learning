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

    loop.run();

    return 0;
}