#include "ros/ros.h"
#include "geometry_msgs/Twist.h"

class TurtleCircleMover
{
public:
    TurtleCircleMover()
    {
        // 퍼블리셔 생성 (geometry_msgs/Twist 메시지를 /turtle1/cmd_vel 주제로 발행)
        pub = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1000);

        // 선형 속도와 각속도를 설정하여 원형 경로를 만듦
        msg.linear.x = 2.0;  // 선형 속도
        msg.angular.z = 1.0; // 각속도
    }

    void move_in_circle()
    {
        ros::Rate loop_rate(10);  // 10Hz 루프 속도 설정

        while (ros::ok())
        {
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
    geometry_msgs::Twist msg;     // 메시지 객체
};

int main(int argc, char **argv)
{
    // ROS 노드 초기화
    ros::init(argc, argv, "oop_circle");

    // TurtleCircleMover 객체 생성 및 거북이 이동
    TurtleCircleMover mover;
    mover.move_in_circle();

    return 0;
}

