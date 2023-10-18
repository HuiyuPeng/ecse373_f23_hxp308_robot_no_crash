#include "ros/ros.h"
#include "std_msgs/String.h"

#include <sstream>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/LaserScan.h>
// #include <sensor_msgs/LaserScan.h>

ros::Publisher *p_pub;
double wall_dist = 1.0;

enum RobotState
{
    MOVE_FORWARD,
    TURN_LEFT
};

RobotState robot_state = MOVE_FORWARD;
sensor_msgs::LaserScan::ConstPtr laser_data;

void chatterCallback(const geometry_msgs::Twist::ConstPtr &msg)
{
    ROS_INFO("des val data");
    p_pub->publish(*msg);
}

void laserCallback(const sensor_msgs::LaserScan::ConstPtr &laserData)
{
    // Fixed indices for a 180-degree view in front
    // int min_index = 45;
    // int max_index = 225;
    ROS_INFO("1");
    int range_size = laserData->ranges.size();
    ROS_INFO("range size %d", range_size);
    int min_index = int(range_size * 45 / 270.0);
    int max_index = int(range_size * 225 / 270.0);
    ROS_INFO("what is min index %d", min_index);
    ROS_INFO("what is max index %d", max_index);
    // ROS_INFO("what is 450 value %f", laserData->ranges[450]);
    for (int i = min_index; i <= max_index; ++i)
    {
        if (laserData->ranges[i] < wall_dist)
        {
            ROS_INFO("Obstacle detected at distance: %f. Setting state to TURN_LEFT.", laserData->ranges[i]);
            robot_state = TURN_LEFT;
            return;
        }
    }
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "stdr_publisher_node");

    // Init the node
    ros::NodeHandle n;

    // Init the subscriber
    ros::Subscriber sub = n.subscribe("des_vel", 10, chatterCallback);
    ros::Subscriber lidar_sub = n.subscribe("laser_0", 10, laserCallback);

    // Init the publisher
    ros::Publisher publisher_handle = n.advertise<geometry_msgs::Twist>("cmd_vel", 1000);

    p_pub = &publisher_handle;

    // Set the frequency of loop in the node
    ros::Rate loop_rate(10);

    // set the wall_dist
    n.param("wall_dist", wall_dist, 0.5);
    ROS_INFO_ONCE("wall_dist began with: [%2.2f]", wall_dist);

    while (ros::ok())
    {
        geometry_msgs::Twist msg;

        switch (robot_state)
        {
        case MOVE_FORWARD:
            ROS_INFO("Moving forward");
            msg.linear.x = 0.5;
            msg.angular.z = 0;
            break;
        case TURN_LEFT:
            ROS_INFO("Moving left");
            msg.linear.x = -0.01;
            msg.angular.z = 0.5;
            robot_state = MOVE_FORWARD;
            break;
        default:
            ROS_INFO("default case");
            break;
        }

        publisher_handle.publish(msg);

        ros::spinOnce();

        loop_rate.sleep();
    }

    ROS_INFO_ONCE("wall_dist is now: [%2.2f]", wall_dist);

    return 0;
}
