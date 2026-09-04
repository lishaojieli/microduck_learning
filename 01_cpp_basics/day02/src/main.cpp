#include "control_loop.hpp"
#include "controller.hpp"
#include "robot.hpp"

int main()
{
    Robot robot;

    Controller controller(
        0.5,
        0.1
    );

    ControlLoop loop(
        robot,
        controller,
        50.0
    );

    loop.run();

    return 0;
}