#include "control_loop.hpp"
#include "controller.hpp"
#include "motion_manager.hpp"
#include "robot.hpp"

#include "control_loop.hpp"
#include "controller.hpp"
#include "motion_manager.hpp"
#include "robot.hpp"

#include <iostream>
#include <thread>

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

    // 控制循环放到单独线程
    std::thread control_thread(
        [&loop]()
        {
            loop.run();
        }
    );

    std::cout
        << "Keyboard Control"
        << std::endl;

    std::cout
        << "s : Stand"
        << std::endl;

    std::cout
        << "q : Squat"
        << std::endl;

    std::cout
        << "x : Exit"
        << std::endl;

    char key;

    while (true)
    {
        std::cin >> key;

        if (key == 's')
        {
            motion_manager.setCommand(
                MotionCommand::Stand
            );

            std::cout
                << "Command: Stand"
                << std::endl;
        }
        else if (key == 'q')
        {
            motion_manager.setCommand(
                MotionCommand::Squat
            );

            std::cout
                << "Command: Squat"
                << std::endl;
        }
        else if (key == 'x')
        {
            std::cout
                << "Exiting..."
                << std::endl;

            break;
        }
        else
        {
            std::cout
                << "Unknown command"
                << std::endl;
        }
    }

    loop.stop();

    control_thread.join();

    return 0;
}