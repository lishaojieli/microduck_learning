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
            bool success =
                mailbox.pushCommand(
                    MotionCommand::Stand
                );

            if (success)
            {
                std::cout
                    << "Command queued: Stand"
                    << std::endl;
            }
            else
            {
                std::cout
                    << "Command queue full!"
                    << std::endl;
            }
        }
        else if (key == 'q')
        {
            bool success =
                mailbox.pushCommand(
                    MotionCommand::Squat
                );

            if (success)
            {
                std::cout
                    << "Command queued: Squat"
                    << std::endl;
            }
            else
            {
                std::cout
                    << "Command queue full!"
                    << std::endl;
            }
        }
    }

    loop.stop();

    control_thread.join();

    return 0;
}