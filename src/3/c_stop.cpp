#include "ros/ros.h"
#include "geometry_msgs/Twist.h"

int main(int argc, char **argv)
{
    // ROS 노드 초기화
    ros::init(argc, argv, "c_stop");
    ros::NodeHandle n;

    // 퍼블리셔 생성 (geometry_msgs/Twist 메시지를 /turtle1/cmd_vel 주제로 발행)
    ros::Publisher pub = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1000);

    // 루프 속도 설정 (10Hz)
    ros::Rate loop_rate(10);

    // 메시지 객체 생성
    geometry_msgs::Twist msg;

    // 선형 속도와 각속도를 설정하여 원형 경로를 만듦
    msg.linear.x = 2.0;  // 선형 속도
    msg.angular.z = 1.0; // 각속도

    // 10초간 이동한 후 정지
    ros::Time start_time = ros::Time::now();  // 시작 시간

    while (ros::ok())
    {
        ros::Duration elapsed_time = ros::Time::now() - start_time;

        if (elapsed_time.toSec() < 10.0)
        {
            // 10초 동안은 이동
            pub.publish(msg);
        }
        else
        {
            // 10초 이후에는 정지
            msg.linear.x = 0.0;
            msg.angular.z = 0.0;
            pub.publish(msg);
        }

        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}

