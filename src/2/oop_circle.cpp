#include "ros/ros.h"
#include "geometry_msgs/Twist.h"

class TurtleCircleMover
{
public:
    TurtleCircleMover()
    {
        pub = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1000);

        msg.linear.x = 2.0; 
        msg.angular.z = 1.0;
    }

    void move_in_circle()
    {
        ros::Rate loop_rate(10);

        while (ros::ok())
        {
            pub.publish(msg);

            ros::spinOnce();
            loop_rate.sleep();
        }
    }

private:
    ros::NodeHandle n;          
    ros::Publisher pub;           
    geometry_msgs::Twist msg;    
};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "oop_circle");

    TurtleCircleMover mover;
    mover.move_in_circle();

    return 0;
}

