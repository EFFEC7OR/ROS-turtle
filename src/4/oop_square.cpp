#include "ros/ros.h"
#include "geometry_msgs/Twist.h"

const double PI = 3.14159265358979323846;

class SquareController
{
public:
    SquareController()
    {
        vel_pub = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);
    }

    void moveSquare(double side_length, double linear_speed, double angular_speed)
    {
        ros::Rate rate(10);
        geometry_msgs::Twist vel_msg;

        while(ros::ok())
        {
            for(int i = 0; i < 4 && ros::ok(); i++)
            {
                vel_msg.linear.x = linear_speed;
                vel_msg.angular.z = 0.0;
                ROS_INFO("Moving straight for side %d.", i+1);
                ros::Time start = ros::Time::now();
                while(ros::Time::now() - start < ros::Duration(side_length / linear_speed) && ros::ok())
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
                while(ros::Time::now() - start < ros::Duration((PI / 2) / angular_speed) && ros::ok())
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
    }

private:
    ros::NodeHandle nh;
    ros::Publisher vel_pub;
};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "oop_square");
    ros::NodeHandle nh;

    SquareController square;

    double side_length = 2.0;    
    double linear_speed = 1.0;    
    double angular_speed = PI / 4; 

    square.moveSquare(side_length, linear_speed, angular_speed);

    return 0;
}
