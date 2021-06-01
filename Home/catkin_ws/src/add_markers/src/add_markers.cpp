#include <ros/ros.h>
#include <ros/console.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <visualization_msgs/Marker.h>
#include <nav_msgs/Odometry.h>
#include <math.h>

double r_x, r_y;
double P_X = 0.0, P_Y = -1.5, P_Z = 0.0;
double D_X = 0.5, D_Y = -1.0, D_Z = 0.0;
bool pick_up = false;
bool drop_off = false;

void odom(const nav_msgs::Odometry::ConstPtr& msg) 
{
	r_x = msg->pose.pose.position.x;
	r_y = msg->pose.pose.position.y;
	
	float distace1;
	float distace2;
	
	if(!pick_up && !drop_off)
	{
		distace1 = sqrt(pow((P_X - r_x), 2) + pow((P_Y - r_y), 2));
		ROS_INFO("Distance to pick up zone = %f", distace1);
		
		if(distace1 <= 0.2)
		{
			ROS_INFO("Arrived at the pick up zone");
			pick_up = true;
		}
	}
	if(pick_up && !drop_off)
	{
		distace2 = sqrt(pow((D_X - r_x), 2) + pow((D_Y - r_y), 2));
		ROS_INFO("Distance to drop off zone = %f", distace2);
		
		if(distace2 <= 0.2)
		{
			ROS_INFO("Arrived at the drop off zone");
			drop_off = true;
		}
	}
}

int main( int argc, char** argv )
{
	ros::init(argc, argv, "add_markers");
  	ros::NodeHandle n;
  	ros::Rate r(1);
  	ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

  	ros::Subscriber odometry_sub = n.subscribe("/odom", 1000, odom);

  	uint32_t shape = visualization_msgs::Marker::CUBE;

  	visualization_msgs::Marker marker;

  	marker.header.frame_id = "map";
  	marker.header.stamp = ros::Time::now();

  	marker.ns = "basic_shapes";
  	marker.id = 0;

  	marker.type = shape;
  	marker.action = visualization_msgs::Marker::ADD;

  	marker.scale.x = 1.0;
  	marker.scale.y = 1.0;
  	marker.scale.z = 1.0;

  	marker.color.r = 0.0f;
  	marker.color.g = 1.0f;
  	marker.color.b = 0.0f;
  	marker.color.a = 1.0;
	

	marker.pose.position.x = P_X;
  	marker.pose.position.y = P_Y;
  	marker.pose.position.z = P_Z;
  	marker.pose.orientation.x = 0.0;
  	marker.pose.orientation.y = 0.0;
  	marker.pose.orientation.z = 0.0;
  	marker.pose.orientation.w = 1.0;
	
	marker.lifetime = ros::Duration();

  	while (ros::ok())
  	{
		while (marker_pub.getNumSubscribers() < 1)
		{
			if (!ros::ok())
			{
				return 0;
			}
			ROS_WARN_ONCE("Please create a subscriber to the marker");
			sleep(1);
		}
		
		if(pick_up)
		{
			marker.action = visualization_msgs::Marker::DELETE;
			ROS_INFO("pickerd up");
			ros::Duration(2.0).sleep();
		}
		
		if(drop_off)
		{
			marker.pose.position.x = D_X;
			marker.pose.position.y = D_Y;
			marker.pose.position.y = D_Z;
			marker.action = visualization_msgs::Marker::ADD;
			ROS_INFO("dropped off");
			ros::Duration(2.0).sleep();
		}
		
		marker_pub.publish(marker);
		
		ros::spinOnce();
	}
	
	return 0;
}
