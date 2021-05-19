#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
// Define a client to send goal requests to the "move_base" server,
// through the "SimpleActionClient"
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

double P_X = 5.0;
double P_Y = 5.0;
double D_X = 10.0;
double D_Y = 10.0;

int main(int argc, char **argv)
{
  //Initialize the simple_navigation_goals node
  ros::init(argc, argv, "pick_objects");

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  //Wait 5 sec for move_base action server to come up
  while (!ac.waitForServer(ros::Duration(5.0)))
  {
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  //goal location
  move_base_msgs::MoveBaseGoal goal;
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  // Request robot to move to Pickup location
  goal.target_pose.pose.position.x = P_X;
  goal.target_pose.pose.position.y = P_Y;
  goal.target_pose.pose.orientation.w = 1.0;

  // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending pick up location");
  ac.sendGoal(goal);
  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached pick up location
  if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
  {

    ROS_INFO("Made it to the pick up location!!!!");
    // sleep for five seconds
    ros::Duration(5).sleep();

    // Request robot to move to Dropoff location
    move_base_msgs::MoveBaseGoal dropOff;
    dropOff.target_pose.header.frame_id = "map";
    dropOff.target_pose.header.stamp = ros::Time::now();
    dropOff.target_pose.pose.position.x = D_X;
    dropOff.target_pose.pose.position.y = D_Y;
    dropOff.target_pose.pose.orientation.w = 1.0;

    ROS_INFO("Robot is travelling to the dropoff zone");
    ac.sendGoal(dropOff);
    ac.waitForResult();
    if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    {
      // Robot reached dropoff zone
      ROS_INFO("Robot dropped the virtual object");
     
      // sleep for five seconds
      ros::Duration(5.0).sleep();
    }
    else
    {
      ROS_INFO("Unable to get to the dropoff zone");
    }
  }
  else
  {
    ROS_INFO("Unable to get to the pickup zone");
  }

  return 0;
}
