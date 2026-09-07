#include "command_mailbox.hpp"

CommandMailbox::CommandMailbox(
    std::size_t max_size
)
    : max_size_(max_size)
{
}

bool CommandMailbox::pushCommand(
    MotionCommand command
)
{
    std::lock_guard<std::mutex> lock(mutex_);

    if (command == MotionCommand::EmergencyStop ||
        command == MotionCommand::Reset)
    {
        while (!commands_.empty())
        {
            commands_.pop();
        }

        commands_.push(command);

        return true;
    }

    if (commands_.size() >= max_size_)
    {
        commands_.pop();
    }

    commands_.push(command);

    return true;
}

MotionCommand CommandMailbox::takeCommand()
{
    std::lock_guard<std::mutex> lock(mutex_);

    if (commands_.empty())
    {
        return MotionCommand::None;
    }

    MotionCommand command =
        commands_.front();

    commands_.pop();

    return command;
}

std::size_t CommandMailbox::size() const
{
    std::lock_guard<std::mutex> lock(mutex_);

    return commands_.size();
}

bool CommandMailbox::empty() const
{
    std::lock_guard<std::mutex> lock(mutex_);

    return commands_.empty();
}