#include "servo.hpp"

#include <iostream>
#include <vector>

int main()
{
    std::vector<Servo> servos;

    servos.emplace_back(1, -1.0, 1.0);
    servos.emplace_back(2, -1.5, 0.0);
    servos.emplace_back(3, -0.8, 0.8);

    servos.emplace_back(4, -1.0, 1.0);
    servos.emplace_back(5, -1.5, 0.0);
    servos.emplace_back(6, -0.8, 0.8);

    servos[0].setTargetPosition(0.3);
    servos[1].setTargetPosition(-0.6);
    servos[2].setTargetPosition(0.3);

    servos[3].setTargetPosition(-0.3);
    servos[4].setTargetPosition(-0.6);
    servos[5].setTargetPosition(-0.3);

    for (Servo& servo : servos)
    {
        servo.update();
    }

    for (const Servo& servo : servos)
    {
        servo.printState();
        std::cout << std::endl;
    }

    return 0;
}