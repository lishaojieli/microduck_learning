#pragma once

#include "motion_manager.hpp"

#include <mutex>

class CommandMailbox
{
public:
    CommandMailbox();

    void setCommand(
        MotionCommand command
    );

    MotionCommand getCommand() const;

private:
    MotionCommand command_;

    mutable std::mutex mutex_;
};