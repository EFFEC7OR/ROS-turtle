#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"
#include <cmath>

class TurtleSquareMover
{
public:
    TurtleSquareMover()
    {
        pub = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1000);
        sub = n.subscribe("/turtle1/pose", 10, &TurtleSquareMover::poseCallback, this);  // poseCallback을 멤버 함수로 연결
    }

    void move_straight(double speed, double distance)
    {
        geometry_msgs::Twist msg;
        msg.linear.x = speed;
        double start_x = current_pose.x;
        double start_y = current_pose.y;

        ros::Rate loop_rate(10);
        while (ros::ok())
        {
            double distance_moved = std::sqrt(std::pow(current_pose.x - start_x, 2) + std::pow(current_pose.y - start_y, 2));
            if (distance_moved >= distance)
            {
                msg.linear.x = 0;
                pub.publish(msg);
                break;
            }

            pub.publish(msg);
            ros::spinOnce();
            loop_rate.sleep();
        }
    }

    void rotate(double angular_speed, double relative_angle)
    {
        geometry_msgs::Twist msg;
        msg.angular.z = angular_speed;

        ros::Rate loop_rate(10);
        double start_time = ros::Time::now().toSec();
        while (ros::ok())
        {
            double current_time = ros::Time::now().toSec();
            double angle_moved = angular_speed * (current_time - start_time);
            if (angle_moved >= relative_angle)
            {
                msg.angular.z = 0;
                pub.publish(msg);
                break;
            }

            pub.publish(msg);
            ros::spinOnce();
            loop_rate.sleep();
        }
    }

    void move_in_square()
    {
        for (int i = 0; i < 4; i++)
        {
            move_straight(2.0, 2.0);  // 선형 속도 2.0, 2m 이동
            ros::Duration(1).sleep();  // 이동 후 잠시 대기

            rotate(M_PI / 2, M_PI / 2);  // 각속도 M_PI/2, 90도 회전
            ros::Duration(1).sleep();    // 회전 후 잠시 대기
        }
    }

private:
    ros::NodeHandle n;
    ros::Publisher pub;
    ros::Subscriber sub;
    turtlesim::Pose current_pose;

    // poseCallback을 멤버 함수로 선언 (static 아님)
    void poseCallback(const turtlesim::Pose::ConstPtr& msg)
    {
        current_pose = *msg;
    }
};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "oop_square");

    TurtleSquareMover mover;
    mover.move_in_square();

    return 0;
}

