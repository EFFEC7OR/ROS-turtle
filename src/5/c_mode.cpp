#include "ros/ros.h"
#include <iostream>
#include <cstdlib> 

int main(int argc, char **argv)
{
    ros::init(argc, argv, "c_mode");
    ros::NodeHandle nh;

    int choice;

    while (ros::ok()) {
        std::cout << "Select mode:\n"
                  << "1. Circular Motion\n"
                  << "2. Square Motion\n"
                  << "3. Stop\n"
                  << "Enter choice: ";
        std::cin >> choice;

        if (choice == 1) {
            std::cout << "Starting Circular Motion...\n";
            system("rosrun ros_turtle c_circle &");
        }
        else if (choice == 2) {
            std::cout << "Starting Square Motion...\n";
            system("rosrun ros_turtle c_square &");
        }
        else if (choice == 3) {
            std::cout << "Stopping all motions...\n";
            system("pkill -f ros_turtle");
        }
        else {
            std::cout << "Invalid choice. Please select 1, 2, or 3.\n";
        }

        std::cout << "-------------------------------\n";
    }

    return 0;
}
