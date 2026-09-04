#include "controller.hpp"

Controller::Controller()
    : target_positions_
      {
          0.3,
          -0.6,
          0.3,
          -0.3,
          -0.6,
          -0.3
      }
{
}

RobotCommand Controller::computeCommand(const RobotState& state)
{
    RobotCommand command;

    command.joint_targets = target_positions_;

    return command;
}