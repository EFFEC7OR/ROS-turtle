#include "ros/ros.h"
#include "geometry_msgs/Twist.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "turtle_circle_motion");
    ros::NodeHandle nh;

    ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);

    geometry_msgs::Twist msg;

    msg.linear.x = 2.0;  
    msg.angular.z = 1.0; 

    ros::Rate rate(10); 
    ros::Time start = ros::Time::now();
    ros::Time last_info_time = ros::Time::now(); 

    while (ros::Time::now() - start < ros::Duration(10))
    {
        pub.publish(msg);

        if (ros::Time::now() - last_info_time >= ros::Duration(1.0))
        {
            ROS_INFO("The turtle is moving in a circle.");
            last_info_time = ros::Time::now(); 
        }

        ros::spinOnce();
        rate.sleep();
    }

    msg.linear.x = 0.0;
    msg.angular.z = 0.0;
    pub.publish(msg);
    ROS_INFO("The turtle moved in a circle for 10 seconds and then stopped.");

    return 0;
}

