#include "command_mailbox.hpp"
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

    CommandMailbox mailbox;

    ControlLoop loop(
        robot,
        controller,
        motion_manager,
        mailbox,
        50.0
    );

    std::thread control_thread(
        [&loop]()
        {
            loop.run();
        }
    );

    std::cout
        << "s : Stand\n"
        << "q : Squat\n"
        << "x : Exit\n";

    char key;

    while (true)
    {
        std::cin >> key;

        if (key == 's')
        {
            mailbox.setCommand(
                MotionCommand::Stand
            );

            std::cout
                << "Command: Stand"
                << std::endl;
        }
        else if (key == 'q')
        {
            mailbox.setCommand(
                MotionCommand::Squat
            );

            std::cout
                << "Command: Squat"
                << std::endl;
        }
        else if (key == 'x')
        {
            break;
        }
    }

    loop.stop();

    control_thread.join();

    return 0;
}