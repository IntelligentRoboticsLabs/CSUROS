#include <ros/ros.h>
#include "tf/transform_datatypes.h"

// MoveIt!
#include <moveit_msgs/PlanningScene.h>
#include <moveit_msgs/AttachedCollisionObject.h>
#include <moveit_msgs/GetStateValidity.h>
#include <moveit_msgs/DisplayRobotState.h>
#include <moveit_msgs/DisplayTrajectory.h>

#include <moveit/move_group_interface/move_group.h>
#include <moveit/robot_model_loader/robot_model_loader.h>
#include <moveit/robot_state/robot_state.h>
#include <moveit/robot_state/conversions.h>

int main( int argc, char** argv )
{
	ros::init(argc, argv, "gripper_manipulation");
	ros::NodeHandle n("~");

	ros::AsyncSpinner spinner(1);
	spinner.start();

	moveit::planning_interface::MoveGroup gripper("gripper");


	// Set values for your gripper here
	const double gripper_open = 0.7;
	const double gripper_closed = -0.6;

	ROS_INFO("Open Gripper");
	gripper.setJointValueTarget({gripper_open});
	gripper.move();
	ros::Duration(3).sleep(); // wait a few seconds here

	ROS_INFO("Close Gripper");
	gripper.setJointValueTarget({gripper_closed});
	gripper.move();

	ros::Duration(3).sleep(); // wait a few seconds here

	ROS_INFO("Pick completed. Waiting for user shutdown (ctrl-c).");
	ros::waitForShutdown();

	return 0;
}
