#include "ros/ros.h"
#include <iostream>
#include <thread>
#include <atomic>
#include <cstdlib>

enum Mode {
    NONE,
    CIRCLE,
    SQUARE
};

class ModeController {
public:
    ModeController() : current_mode(NONE), stop_flag(false) {}

    void start() {
        input_thread = std::thread(&ModeController::handleUserInput, this);

        while (ros::ok()) {
            if (current_mode == CIRCLE && !stop_flag) {
                std::cout << "Starting Circular Motion...\n";
                system("rosrun ros_turtle c_circle &");
                current_mode = NONE; 
            }
            else if (current_mode == SQUARE && !stop_flag) {
                std::cout << "Starting Square Motion...\n";
                system("rosrun ros_turtle c_square &");
                current_mode = NONE;
            }

            ros::spinOnce();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        if (input_thread.joinable()) {
            input_thread.join();
        }
    }

private:
    ros::NodeHandle nh;
    std::thread input_thread;
    std::atomic<Mode> current_mode;
    std::atomic<bool> stop_flag;

    void handleUserInput() {
        int choice;
        while (ros::ok()) {
            std::cout << "Select mode:\n"
                      << "1. Circular Motion\n"
                      << "2. Square Motion\n"
                      << "3. Stop\n"
                      << "Enter choice: ";
            std::cin >> choice;

            if (choice == 1) {
                current_mode = CIRCLE;
                stop_flag = false;
            }
            else if (choice == 2) {
                current_mode = SQUARE;
                stop_flag = false;
            }
            else if (choice == 3) {
                std::cout << "Stopping all motions...\n";
                system("pkill -f ros_turtle");
                stop_flag = true;
            }
            else {
                std::cout << "Invalid choice. Please select 1, 2, or 3.\n";
            }

            std::cout << "-------------------------------\n";
        }
    }
};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "oop_mode");
    ros::NodeHandle nh;

    ModeController controller;
    controller.start();

    return 0;
}
