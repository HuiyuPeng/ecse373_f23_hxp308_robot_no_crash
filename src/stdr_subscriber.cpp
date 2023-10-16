#include "ros/ros.h"
#include "std_msgs/String.h"

#include <geometry_msgs/Twist.h>
#include <sensor_msgs/LaserScan.h>
#include "robot_no_crash/topic_name.h"

ros::Publisher *p_pub;

void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
    p_pub->publish(*msg);
}

int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "stdr_subscriber_node");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("des_vel", 10, chatterCallback);
  ros::Publisher publisher_handle = n.advertise<geometry_msgs::Twist>("cmd_vel", 10);
  p_pub = &publisher_handle;
  ros::spin();

  return 0;
}