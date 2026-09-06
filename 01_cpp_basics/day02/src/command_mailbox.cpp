#include "command_mailbox.hpp"

CommandMailbox::CommandMailbox()
    : command_(MotionCommand::None)
{
}

void CommandMailbox::setCommand(
    MotionCommand command
)
{
    std::lock_guard<std::mutex> lock(mutex_);

    command_ = command;
}

MotionCommand CommandMailbox::getCommand() const
{
    std::lock_guard<std::mutex> lock(mutex_);

    return command_;
}