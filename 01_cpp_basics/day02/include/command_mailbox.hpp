#pragma once

#include "motion_manager.hpp"

#include <cstddef>
#include <mutex>
#include <queue>

class CommandMailbox
{
public:
    explicit CommandMailbox(
        std::size_t max_size = 10
    );

    bool pushCommand(
        MotionCommand command
    );

    MotionCommand takeCommand();

    std::size_t size() const;

    bool empty() const;

private:
    std::queue<MotionCommand> commands_;

    std::size_t max_size_;

    mutable std::mutex mutex_;
};