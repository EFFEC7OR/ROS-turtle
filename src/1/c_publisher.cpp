#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include <iostream>

int main(int argc, char **argv)
{
    // ROS 노드 초기화
    ros::init(argc, argv, "c_publisher");
    ros::NodeHandle n;

    // 퍼블리셔 생성 (geometry_msgs/Twist 메시지를 /robot_speed 주제로 발행)
    ros::Publisher pub = n.advertise<geometry_msgs::Twist>("/robot_speed", 1000);

    // 루프 속도 설정 (10Hz)
    ros::Rate loop_rate(10);

    // 메시지 객체 생성
    geometry_msgs::Twist msg;

    while (ros::ok())
    {
        // 사용자로부터 선형 속도와 각속도 입력받기
        std::cout << "선형 속도 입력: ";
        std::cin >> msg.linear.x;
        std::cout << "각속도 입력: ";
        std::cin >> msg.angular.z;

        // 메시지 발행
        pub.publish(msg);

        // ROS 콜백 함수 호출
        ros::spinOnce();

        // 루프 속도 유지
        loop_rate.sleep();
    }

    return 0;
}

