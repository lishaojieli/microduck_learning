#include "command_mailbox.hpp"
#include "control_loop.hpp"
#include "controller.hpp"
#include "motion_manager.hpp"
#include "robot.hpp"
#include "safety_monitor.hpp"

#include <iostream>
#include <thread>

int main()
{
    Robot robot;

    Controller controller(
        1,
        0.0
    );

    MotionManager motion_manager;

    CommandMailbox mailbox;

    SafetyMonitor safety_monitor(
        0.1,   // max joint velocity rad/s
        0.1    // max pitch rad
    );

    ControlLoop loop(
        robot,
        controller,
        motion_manager,
        mailbox,
        safety_monitor,
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
            mailbox.pushCommand(
                MotionCommand::Stand
            );
        std::cout
            << "Queued Stand"
            << " | Queue size: "
            << mailbox.size()
            << std::endl;
        }
        else if (key == 'q')
        {
            mailbox.pushCommand(
                MotionCommand::Squat
            );
        std::cout
            << "Queued Squat"
            << " | Queue size: "
            << mailbox.size()
            << std::endl;
        }
        else if (key == 'p')
        {
            mailbox.pushCommand(
                MotionCommand::Stop
            );
        std::cout
            << "Queued Stop"
            << " | Queue size: "
            << mailbox.size()
            << std::endl;
        }
        else if (key == 'e')
        {
            mailbox.pushCommand(
                MotionCommand::EmergencyStop
            );
        std::cout
            << "Queued EmergencyStop"
            << " | Queue size: "
            << mailbox.size()
            << std::endl;
        }
        else if (key == 'r')
        {
            mailbox.pushCommand(
                MotionCommand::Reset
            );
        std::cout
            << "Queued Reset"
            << " | Queue size: "
            << mailbox.size()
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