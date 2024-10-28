#include "ros/ros.h"
#include "geometry_msgs/Twist.h"

class CircleMotionController
{
public:
    CircleMotionController()
    {
        pub = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);
    }

    void moveInCircle(double linear_speed, double angular_speed, double duration)
    {
        geometry_msgs::Twist msg;

        msg.linear.x = linear_speed;
        msg.angular.z = angular_speed;

        ros::Rate rate(10);
        ros::Time start = ros::Time::now();
        ros::Time last_info_time = ros::Time::now();

        while (ros::Time::now() - start < ros::Duration(duration))
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
    }

private:
    ros::NodeHandle nh;
    ros::Publisher pub;
};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "oop_turtle_circle_motion");

    CircleMotionController circleController;

    circleController.moveInCircle(2.0, 1.0, 10.0);

    return 0;
}

