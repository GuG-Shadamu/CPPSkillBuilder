/*
 * @Author: Tairan Gao
 * @Date:   2023-09-22 16:54:34
 * @Last Modified by:   Tairan Gao
 * @Last Modified time: 2023-09-26 12:45:51
 */
#include <iostream>
#include <cmath>

class ClockAngleCalculator
{
public:
    // Function to calculate the angle between the hour and minute hands of a clock
    // given the time in hours and minutes
    static double calculateAngle(int hours, int minutes)
    {
        hours = hours % 12;

        double angle_per_hour{30.0};
        double angle_per_minute{6.0};

        double minute_angle{minutes * 6.0};
        double hour_angle{hours * 30.0};
        double add_on_angle{30 * minutes / 60.0};
        hour_angle = hour_angle + add_on_angle;

        double sol = std::abs(hour_angle - minute_angle);

        return std::min(360 - sol, sol);
    }
};

int main()
{
    int hours, minutes;

    // Input the time
    std::cout << "Enter the time (hours and minutes): ";
    std::cin >> hours >> minutes;

    // Validate input
    if (hours < 0 || hours > 12 || minutes < 0 || minutes > 59)
    {
        std::cerr << "Invalid time input!\n";
        return 1;
    }

    // Calculate the angle
    double angle = ClockAngleCalculator::calculateAngle(hours, minutes);

    // Output the result
    std::cout << "The angle between the hour and minute hands is: " << angle << " degrees\n";

    return 0;
}
