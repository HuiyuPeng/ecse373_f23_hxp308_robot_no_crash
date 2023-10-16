#include "ros/ros.h"
#include "std_msgs/String.h"

#include <sstream>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/LaserScan.h>
//#include <sensor_msgs/LaserScan.h>

ros::Publisher *p_pub;
double wall_dist = 1.0;

enum RobotState {
MOVE_FORWARD,
TURN_LEFT
};

RobotState robot_state = MOVE_FORWARD;

void chatterCallback(const geometry_msgs::Twist::ConstPtr& msg)
{
ROS_INFO("des val data");
p_pub->publish(*msg);
}

void laserCallback(const sensor_msgs::LaserScan::ConstPtr& laserData) 
{
// Fixed indices for a 180-degree view in front
int min_index = 45;
int max_index = 225;

for (int i = min_index; i <= max_index; ++i) {
if (laserData->ranges[i] < wall_dist) {
ROS_INFO("WALL DISTANT: %f", wall_dist);
ROS_INFO("Obstacle detected at distance: %f. Setting state to TURN_LEFT.", laserData->ranges[i]);
robot_state = TURN_LEFT;
return;
}
}

double cur_min = 1000000000.0;
int idx = -1;
for (int i = min_index; i <= max_index; ++i) {
if (laserData->ranges[i] < cur_min) {
cur_min = laserData->ranges[i];
idx = i;
}
}

ROS_INFO("No close obstacles detected, angle: %d. dist: %f", idx, cur_min);
}


int main(int argc, char **argv)
{
ros::init(argc, argv, "stdr_publisher_node");

//Init the node
ros::NodeHandle n;

// Init the subscriber
ros::Subscriber sub = n.subscribe("des_vel", 1000, chatterCallback);
ros::Subscriber lidar_sub = n.subscribe("laser_0", 1000, laserCallback);

// Init the publisher
ros::Publisher publisher_handle = n.advertise<geometry_msgs::Twist>("cmd_vel", 1000);

p_pub = &publisher_handle;

// Set the frequency of loop in the node
ros::Rate loop_rate(10);

// set the wall_dist
n.param("wall_dist", wall_dist, 0.5);
ROS_INFO_ONCE("wall_dist began with: [%2.2f]", wall_dist);

ros::Time turn_start_time;

while(ros::ok())
{
geometry_msgs::Twist msg;

switch (robot_state) {
case MOVE_FORWARD:
msg.linear.x = 0.2; // Move forward at a speed of 0.5 m/s
msg.angular.z = 0; // No angular velocity
break;
case TURN_LEFT:
msg.linear.x = 0; // No linear movement
msg.angular.z = M_PI / 5; // Start turning at 45 degrees per second
robot_state = MOVE_FORWARD;
break;
}

publisher_handle.publish(msg);

ros::spinOnce(); // Handle ROS events

loop_rate.sleep(); // Sleep for the rest of the cycle, to maintain the loop rate
}

ROS_INFO_ONCE("wall_dist is now: [%2.2f]", wall_dist);

return 0;
}
