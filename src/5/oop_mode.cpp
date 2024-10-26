#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include <iostream>
#include <cmath>

class TurtleMover
{
public:
    TurtleMover()
    {
        pub = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1000);
    }

    void move_straight(double speed, double distance)
    {
        geometry_msgs::Twist msg;
        msg.linear.x = speed;
        ros::Rate loop_rate(10);

        for (int i = 0; i < 10 * distance; ++i)
        {
            pub.publish(msg);
            ros::spinOnce();
            loop_rate.sleep();
        }
        msg.linear.x = 0;
        pub.publish(msg);
    }

    void rotate(double angular_speed, double relative_angle)
    {
        geometry_msgs::Twist msg;
        msg.angular.z = angular_speed;
        ros::Rate loop_rate(10);

        for (int i = 0; i < 10 * relative_angle / angular_speed; ++i)
        {
            pub.publish(msg);
            ros::spinOnce();
            loop_rate.sleep();
        }
        msg.angular.z = 0;
        pub.publish(msg);
    }

    void move_in_circle()
    {
        geometry_msgs::Twist msg;
        msg.linear.x = 2.0;
        msg.angular.z = 1.0;
        ros::Rate loop_rate(10);

        while (ros::ok())
        {
            pub.publish(msg);
            ros::spinOnce();
            loop_rate.sleep();
        }
    }

    void move_in_square()
    {
        for (int i = 0; i < 4; i++)
        {
            move_straight(2.0, 2.0);
            rotate(M_PI / 2, M_PI / 2);
        }
    }

    void stop()
    {
        geometry_msgs::Twist msg;
        msg.linear.x = 0.0;
        msg.angular.z = 0.0;
        pub.publish(msg);
    }

    void choose_mode(int mode)
    {
        if (mode == 1)
        {
            move_in_circle();
        }
        else if (mode == 2)
        {
            move_in_square();
        }
        else if (mode == 3)
        {
            stop();
        }
    }

private:
    ros::NodeHandle n;
    ros::Publisher pub;
};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "oop_mode");

    TurtleMover mover;

    int mode;
    std::cout << "모드를 선택하세요 (1: 원 운동, 2: 정사각형 운동, 3: 정지): ";
    std::cin >> mode;

    mover.choose_mode(mode);

    return 0;
}

