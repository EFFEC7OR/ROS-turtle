#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include <iostream>

class RobotSpeedPublisher
{
public:
    RobotSpeedPublisher()
    {
        // 퍼블리셔 생성
        pub = n.advertise<geometry_msgs::Twist>("/robot_speed", 1000);
    }

    void publish_speed()
    {
        ros::Rate loop_rate(10);  // 10Hz 루프 속도 설정
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
            loop_rate.sleep();
        }
    }

private:
    ros::NodeHandle n;            // 노드 핸들
    ros::Publisher pub;           // 퍼블리셔
};

int main(int argc, char **argv)
{
    // ROS 노드 초기화
    ros::init(argc, argv, "oop_publisher");

    // RobotSpeedPublisher 객체 생성 및 퍼블리셔 실행
    RobotSpeedPublisher node;
    node.publish_speed();

    return 0;
}

