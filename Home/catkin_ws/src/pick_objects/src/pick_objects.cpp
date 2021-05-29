#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

double X = 0.0;
double Y = -1.5;
double Z = 0.0;

double X_2 = 0.5;
double Y_2 = -1.0;
double Z_2 = 0.0;


int main(int argc, char** argv)
{
	// Initialize the simple_navigation_goals node
	ros::init(argc, argv, "pick_objects");

	// Nodehandle to set boolean params on Parameter Server
	ros::NodeHandle nh;
	nh.setParam("robot_at_pickup_zone", false);
	nh.setParam("robot_at_dropoff_zone", false);

	// tell the action client "move_base" that we want to spin a thread by default
	MoveBaseClient ac("move_base", true);

	// Wait 5 sec for move_base action server to come up
	while(!ac.waitForServer(ros::Duration(5.0)))
	{
		ROS_INFO("Waiting for the move_base action server to come up");
	}

	move_base_msgs::MoveBaseGoal goal;

	// set up the frame parameters
	goal.target_pose.header.frame_id = "map";
	goal.target_pose.header.stamp = ros::Time::now();

	// GO TO PICK-UP LOCATION
	goal.target_pose.pose.position.x = X;
	goal.target_pose.pose.position.y = Y; 
	goal.target_pose.pose.orientation.w = 1.0;
	goal.target_pose.pose.orientation.z = Z;

	// Send the goal position and orientation for the robot to reach
	ROS_INFO("Sending pick-up location coordinates");
	ac.sendGoal(goal);

	// Wait an infinite time for the results (blocking)
	ac.waitForResult();

	// Check if the robot reached its goal
	if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
	{
		ROS_INFO("Reached pickup zone");
		nh.setParam("robot_at_pickup_zone", true);
	}
	else
	{
		ROS_WARN_ONCE("Failed to reach pick up zone!");
	}

	ros::Duration(5).sleep(); // sleep for 5 seconds

	// GO TO DROP-OFF LOCATION
	goal.target_pose.pose.position.x = X_2;
	goal.target_pose.pose.position.y = Y_2; 
	goal.target_pose.pose.orientation.w = 0.0;
	goal.target_pose.pose.orientation.z = Z_2;

	// Send the goal position and orientation for the robot to reach
	ROS_INFO("Sending drop-off location coordinates");
	ac.sendGoal(goal);

	// Wait an infinite time for the results (blocking)
	ac.waitForResult();

	// Check if the robot reached its goal
	if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
	{
		ROS_INFO("Reached drop-off zone");
		nh.setParam("robot_at_dropoff_zone", true);
	}
	else
	{
		ROS_INFO("Failed to reach drop off zone!");
	}

	while (true)
	{
		if (!ros::ok())
           		return 0;
  	}

}
