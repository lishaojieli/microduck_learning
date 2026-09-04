#include "controller.hpp"

#include <iostream>

Controller::Controller(
    double kp,
    double kd
)
    : kp_(kp),
      kd_(kd),
      desired_positions_
      {
          0.0,
          0.0,
          0.0,
          0.0,
          0.0,
          0.0
      }
{
}

void Controller::setDesiredPositions(
    const std::vector<double>& positions
)
{
    if (positions.size() != desired_positions_.size())
    {
        std::cout
            << "Invalid desired position size!"
            << std::endl;

        return;
    }

    desired_positions_ = positions;
}

RobotCommand Controller::computeCommand(
    const RobotState& state
)
{
    RobotCommand command;

    command.joint_targets.resize(
        desired_positions_.size()
    );

    for (std::size_t i = 0;
         i < desired_positions_.size();
         ++i)
    {
        double position_error =
            desired_positions_[i]
            - state.positions[i];

        double control =
            kp_ * position_error
            - kd_ * state.velocities[i];

        command.joint_targets[i] =
            state.positions[i] + control;
    }

    return command;
}