#include "ros/ros.h"
#include "geometry_msgs/Twist.h"

const double PI = 3.14159265358979323846;

int main(int argc, char **argv)
{
    ros::init(argc, argv, "c_square");
    ros::NodeHandle nh;

    ros::Publisher vel_pub = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);

    ros::Rate rate(10);

    geometry_msgs::Twist vel_msg;

    double linear_speed = 1.0;   
    double side_length = 2.0;     
    double linear_duration = side_length / linear_speed; 

    double angular_speed = PI / 4; 
    double angular_duration = (PI / 2) / angular_speed;

    while(ros::ok())
    {
        for(int i = 0; i < 4 && ros::ok(); i++)
        {
            vel_msg.linear.x = linear_speed;
            vel_msg.angular.z = 0.0;
            ROS_INFO("Moving straight for side %d.", i+1);
            ros::Time start = ros::Time::now();
            while(ros::Time::now() - start < ros::Duration(linear_duration) && ros::ok())
            {
                vel_pub.publish(vel_msg);
                ros::spinOnce();
                rate.sleep();
            }

            vel_msg.linear.x = 0.0;
            vel_pub.publish(vel_msg);
            ros::Duration(1.0).sleep(); 

            vel_msg.angular.z = angular_speed;
            ROS_INFO("Rotating for side %d.", i+1);
            start = ros::Time::now();
            while(ros::Time::now() - start < ros::Duration(angular_duration) && ros::ok())
            {
                vel_pub.publish(vel_msg);
                ros::spinOnce();
                rate.sleep();
            }

            vel_msg.angular.z = 0.0;
            vel_pub.publish(vel_msg);
            ros::Duration(1.0).sleep();
        }
    }

    vel_msg.linear.x = 0.0;
    vel_msg.angular.z = 0.0;
    vel_pub.publish(vel_msg);
    ROS_INFO("Square movement completed.");

    return 0;
}
