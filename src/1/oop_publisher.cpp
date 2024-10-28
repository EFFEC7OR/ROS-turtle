#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include <iostream>

// 퍼블리셔 클래스를 선언
class SpeedPublisher
{
private:
    ros::Publisher pub;  
    ros::NodeHandle n; 
    geometry_msgs::Twist msg;

public:
    SpeedPublisher()
    {
        pub = n.advertise<geometry_msgs::Twist>("/robot_speed", 1000);
    }

    void publish_speed()
    {
        std::cout << "선형 속도 입력: ";
        std::cin >> msg.linear.x;
        std::cout << "각속도 입력: ";
        std::cin >> msg.angular.z;

        std::cout << "발행할 메시지: 선형 속도 = " << msg.linear.x << ", 각속도 = " << msg.angular.z << std::endl;

        pub.publish(msg);

        std::cout << "메시지가 /robot_speed로 발행되었습니다." << std::endl;
    }
};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "oop_publisher");

    SpeedPublisher speed_pub;

    ros::Rate loop_rate(10);

    while (ros::ok())
    {
        speed_pub.publish_speed();

        ros::spinOnce();

        loop_rate.sleep();
    }

    return 0;
}
