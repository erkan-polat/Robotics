#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <nav_msgs/Odometry.h>


double X = 1.7;
double Y = 3.5;
double Z = 0.0;

double X_2 = 0.5;
double Y_2 = -1.0;
double Z_2 = 0.0;

int main( int argc, char** argv )
{
    ros::init(argc, argv, "add_markers"); 
    ros::NodeHandle n;
    ros::Rate r(1);


    ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

    visualization_msgs::Marker marker;


    marker.header.frame_id = "map"; 
    marker.header.stamp = ros::Time::now();


    marker.ns = "add_markers"; 
    marker.id = 0;

    marker.action = visualization_msgs::Marker::ADD;


    marker.pose.position.x = X; 
    marker.pose.position.y = Y; 
    marker.pose.position.z = Z;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;


    marker.scale.x = 0.1;
    marker.scale.y = 0.1;
    marker.scale.z = 0.1;


    marker.color.r = 0.0f;
    marker.color.g = 0.0f;
    marker.color.b = 1.0f;
    marker.color.a = 1.0;


    marker.lifetime = ros::Duration(5); 
    while (ros::ok())
    {

    while (marker_pub.getNumSubscribers() < 1)
    {
        if (!ros::ok()) 
	{
        return 0;
	}
        ROS_WARN_ONCE("Please create a subscriber to the marker!");
        sleep(1);
    }
    marker_pub.publish(marker);


    ros::Duration(5.0).sleep(); 

    visualization_msgs::Marker marker_drop;

    marker_drop.header.frame_id = "map"; 
    marker_drop.header.stamp = ros::Time::now();

    marker_drop.ns = "add_markers"; 
    marker_drop.id = 0;

    marker_drop.action = visualization_msgs::Marker::ADD;


    marker_drop.pose.position.x = X_2; 
    marker_drop.pose.position.y = Y_2; 
    marker_drop.pose.position.z = Z_2;
    marker_drop.pose.orientation.x = 0.0;
    marker_drop.pose.orientation.y = 0.0;
    marker_drop.pose.orientation.z = 0.0;
    marker_drop.pose.orientation.w = 1.0;


    marker_drop.scale.x = 1.0;
    marker_drop.scale.y = 1.0;
    marker_drop.scale.z = 1.0;


    marker_drop.color.r = 0.0f;
    marker_drop.color.g = 0.0f;
    marker_drop.color.b = 1.0f;
    marker_drop.color.a = 1.0;

    marker_drop.lifetime = ros::Duration(5); 


    while (marker_pub.getNumSubscribers() < 1)
    {
        if (!ros::ok()) 
	return 0;

        ROS_WARN_ONCE("subscriber");
        sleep(1);
    }


    ros::Duration().sleep(); 


    return 0;
}
}
