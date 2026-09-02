#pragma once

class Servo
{
public:
    Servo(
        int id,
        double min_position,
        double max_position,
        double max_velocity
    );

    void setTargetPosition(double target_position);

    void update(double dt);

    void printState() const;

    double getCurrentPosition() const;
    double getTargetPosition() const;

private:
    int id_;

    double current_position_;
    double target_position_;

    double min_position_;
    double max_position_;

    double max_velocity_;
};