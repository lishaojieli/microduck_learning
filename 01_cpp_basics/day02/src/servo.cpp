#include "servo.hpp"

#include <iostream>

Servo::Servo(
    int id,
    double min_position,
    double max_position
)
    : id_(id),
      current_position_(0.0),
      target_position_(0.0),
      min_position_(min_position),
      max_position_(max_position)
{
}

void Servo::setTargetPosition(double target_position)
{
    if (target_position > max_position_)
    {
        target_position_ = max_position_;
    }
    else if (target_position < min_position_)
    {
        target_position_ = min_position_;
    }
    else
    {
        target_position_ = target_position;
    }
}

void Servo::update()
{
    current_position_ = target_position_;
}

void Servo::printState() const
{
    std::cout << "Servo ID: "
              << id_
              << std::endl;

    std::cout << "Current position: "
              << current_position_
              << " rad"
              << std::endl;

    std::cout << "Target position: "
              << target_position_
              << " rad"
              << std::endl;
}