#include <iostream>
#include <vector>

class Servo
{
public:
    Servo(
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

    void setTargetPosition(double target_position)
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

    void update()
    {
        current_position_ = target_position_;
    }

    void printState() const
    {
        std::cout << "Servo ID: " << id_ << std::endl;
        std::cout << "Current position: "
                  << current_position_
                  << " rad"
                  << std::endl;

        std::cout << "Target position: "
                  << target_position_
                  << " rad"
                  << std::endl;
    }

private:
    int id_;

    double current_position_;
    double target_position_;

    double min_position_;
    double max_position_;
};

int main()
{
    std::vector<Servo> servos;

    servos.emplace_back(1, -1.0, 1.0);
    servos.emplace_back(2, -1.5, 0.0);
    servos.emplace_back(3, -0.8, 0.8);

    servos[0].setTargetPosition(0.3);
    servos[1].setTargetPosition(-0.6);
    servos[2].setTargetPosition(0.3);

    servos[0].update();
    servos[1].update();
    servos[2].update();

    servos[0].printState();
    servos[1].printState();
    servos[2].printState();

    return 0;
}