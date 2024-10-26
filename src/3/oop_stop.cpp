#include "ros/ros.h"
#include "geometry_msgs/Twist.h"

class TurtleMover
{
public:
    TurtleMover()
    {
        // 퍼블리셔 생성
        pub = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1000);

        // 선형 속도와 각속도를 설정
        msg.linear.x = 2.0;  // 선형 속도
        msg.angular.z = 1.0; // 각속도
    }

    void move_and_stop()
    {
        ros::Rate loop_rate(10);  // 10Hz 루프 속도 설정
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
                stop();
            }

            ros::spinOnce();
            loop_rate.sleep();
        }
    }

private:
    ros::NodeHandle n;            // 노드 핸들
    ros::Publisher pub;           // 퍼블리셔
    geometry_msgs::Twist msg;     // 메시지 객체

    // 정지 메서드
    void stop()
    {
        msg.linear.x = 0.0;
        msg.angular.z = 0.0;
        pub.publish(msg);
    }
};

int main(int argc, char **argv)
{
    // ROS 노드 초기화
    ros::init(argc, argv, "oop_stop");

    // TurtleMover 객체 생성 및 거북이 이동 후 정지
    TurtleMover mover;
    mover.move_and_stop();

    return 0;
}

