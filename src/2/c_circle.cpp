#include "ros/ros.h"
#include "geometry_msgs/Twist.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "c_circle");
    ros::NodeHandle n;

    ros::Publisher pub = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1000);

    ros::Rate loop_rate(10);

    geometry_msgs::Twist msg;

    msg.linear.x = 2.0; 
    msg.angular.z = 1.0;

    while (ros::ok())
    {
        pub.publish(msg);

        ros::spinOnce();

        loop_rate.sleep();
    }

    return 0;
}

