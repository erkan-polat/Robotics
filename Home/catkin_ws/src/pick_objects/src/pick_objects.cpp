#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

double X = 0.0;
double Y = -2.5;
double Z = 0.0;

double X_2 = 0.5;
double Y_2 = -1.0;
double Z_2 = 0.0;

int main(int argc, char **argv)
{
  ros::init(argc, argv, "pick_objects");

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  //wait for the action server to come up
  while (!ac.waitForServer(ros::Duration(5.0)))
  {
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;


  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  // Request robot to move to Pickup location
  goal.target_pose.pose.position.x = X;
  goal.target_pose.pose.position.y = Y;
  goal.target_pose.pose.orientation.w = 1.0;

  ROS_INFO("Robot is travelling to the pickup zone");
  ac.sendGoal(goal);
  ac.waitForResult();

  if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
  {

    ROS_INFO("Robot picked up the virtual object");
    // Wait for 5 seconds
    ros::Duration(5).sleep();

    // Request robot to move to Dropoff location
    goal.target_pose.pose.position.x = X_2;
    goal.target_pose.pose.position.y = Y_2;
    goal.target_pose.pose.orientation.w = 1.0;

    ROS_INFO("Robot is travelling to the dropoff zone");
    ac.sendGoal(goal);
    ac.waitForResult();
    if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    {
      // Robot reached dropoff zone
      ROS_INFO("Robot dropped the virtual object");
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
