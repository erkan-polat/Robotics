#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <nav_msgs/Odometry.h>


double X = 0.0;
double Y = -1.5;
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

	bool p_z = false;
	bool d_z = false;

	visualization_msgs::Marker marker;
	marker.type = visualization_msgs::Marker::CUBE;
	marker.header.frame_id = "map";

	marker.ns = "add_markers";
	marker.id = 0;

	marker.pose.position.x = X;
	marker.pose.position.y = Y;
	marker.pose.position.z = Z;
	marker.pose.orientation.x = 0.0;
	marker.pose.orientation.y = 0.0;
	marker.pose.orientation.z = 0.0;
	marker.pose.orientation.w = 1.0;

	marker.scale.x = 0.2;
	marker.scale.y = 0.2;
	marker.scale.z = 0.01;

	marker.color.r = 0.0f;
	marker.color.g = 0.0f;
	marker.color.b = 1.0f;
	marker.color.a = 1.0;

	while (ros::ok())
	{

		marker.header.stamp = ros::Time::now();
		marker.action = visualization_msgs::Marker::ADD;

		marker.lifetime = ros::Duration();


		while (marker_pub.getNumSubscribers() < 1)
		{
			if (!ros::ok())
			{
				return 0;
			}
			ROS_WARN_ONCE("Please create a subscriber to the marker");
			sleep(1);
		}
		marker_pub.publish(marker);
		
		r.sleep();
		n.getParam("robot_at_pickup_zone", p_z);
		if (p_z)
			break;
	}  

	ROS_INFO("Deleting marker");
	marker.action = visualization_msgs::Marker::DELETE;
	marker_pub.publish(marker);


	while (true)   
	{
		n.getParam("robot_at_dropoff_zone", d_z);
		if (d_z)
			break;
	}

	marker.pose.position.x = X_2;
	marker.pose.position.y = Y_2;
	marker.pose.position.z = Z_2;
	marker.pose.orientation.x = 0.0;
	marker.pose.orientation.y = 0.0;
	marker.pose.orientation.z = 0.0;
	marker.pose.orientation.w = 1.0;

	ROS_INFO("Adding marker at drop-off location");
	while (ros::ok())
	{
		
		marker.header.stamp = ros::Time::now();
		marker.action = visualization_msgs::Marker::ADD;
		marker.lifetime = ros::Duration();


		while (marker_pub.getNumSubscribers() < 1)
		{
			if (!ros::ok())
			{
				return 0;
			}
			ROS_WARN_ONCE("Please create a subscriber to the marker");
			sleep(1);
		}
		marker_pub.publish(marker);
		
		r.sleep();
	}  
}
