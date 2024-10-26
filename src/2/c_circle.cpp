#include "ros/ros.h"
#include "geometry_msgs/Twist.h"

int main(int argc, char **argv)
{
    // ROS 노드 초기화
    ros::init(argc, argv, "c_circle");
    ros::NodeHandle n;

    // 퍼블리셔 생성 (geometry_msgs/Twist 메시지를 /turtle1/cmd_vel 주제로 발행)
    ros::Publisher pub = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1000);

    // 루프 속도 설정 (10Hz)
    ros::Rate loop_rate(10);

    // 메시지 객체 생성
    geometry_msgs::Twist msg;

    // 선형 속도와 각속도를 설정하여 원형 경로를 만듦
    msg.linear.x = 2.0;  // 선형 속도 (거북이가 앞으로 나아가는 속도)
    msg.angular.z = 1.0; // 각속도 (거북이가 회전하는 속도)

    while (ros::ok())
    {
        // 메시지 발행
        pub.publish(msg);

        // ROS 콜백 함수 호출
        ros::spinOnce();

        // 루프 속도 유지
        loop_rate.sleep();
    }

    return 0;
}

