#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

double P_X = 0.0, P_Y = -1.5;
double D_X = 0.5, D_Y = -1.0;

int main(int argc, char **argv)
{
  ros::init(argc, argv, "pick_objects");


  MoveBaseClient ac("move_base", true);

  while (!ac.waitForServer(ros::Duration(5.0)))
  {
    ROS_INFO("Waiting for the move_base");
  }

  move_base_msgs::MoveBaseGoal goal;

  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();


  goal.target_pose.pose.position.x = P_X;
  goal.target_pose.pose.position.y = P_Y;
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
    goal.target_pose.pose.position.x = D_X;
    goal.target_pose.pose.position.y = D_Y;
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
