#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include <iostream>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "c_publisher");
    ros::NodeHandle n;

    ros::Publisher pub = n.advertise<geometry_msgs::Twist>("/robot_speed", 1000);

    ros::Rate loop_rate(10);

    geometry_msgs::Twist msg;

    while (ros::ok())
    {
        std::cout << "선형 속도 입력: ";
        std::cin >> msg.linear.x;
        std::cout << "각속도 입력: ";
        std::cin >> msg.angular.z;

        std::cout << "발행할 메시지: 선형 속도 = " << msg.linear.x << ", 각속도 = " << msg.angular.z << std::endl;

        pub.publish(msg);

        std::cout << "메시지가 /robot_speed로 발행되었습니다." << std::endl;

        ros::spinOnce();

        loop_rate.sleep();
    }

    return 0;
}
