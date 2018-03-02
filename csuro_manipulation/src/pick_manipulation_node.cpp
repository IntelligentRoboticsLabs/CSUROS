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
	ros::init(argc, argv, "pick_manipulation");
	ros::NodeHandle n("~");

	ros::AsyncSpinner spinner(1);
	spinner.start();

	moveit::planning_interface::MoveGroup group("arm");
	moveit::planning_interface::MoveGroup gripper("gripper");

	group.setPoseReferenceFrame("base_link"); // plan w.r.t. base_link frame by default

	ros::Publisher display_publisher = n.advertise<moveit_msgs::DisplayTrajectory>("/move_group/display_planned_path", 1, true);
	moveit_msgs::DisplayTrajectory display_trajectory;

	ROS_INFO("Reference frame: %s", group.getPlanningFrame().c_str());
	ROS_INFO("Endeffector frame: %s", group.getEndEffectorLink().c_str());

	// Set values for your gripper here
	const double gripper_open = 0.7; 
	const double gripper_closed = -0.6;

	group.setGoalPositionTolerance(0.04);
	group.setGoalOrientationTolerance(0.1);
	group.allowReplanning(true);

	//GOING TO INIT POS
	geometry_msgs::Pose target_pose0;
	target_pose0.orientation = tf::createQuaternionMsgFromRollPitchYaw(-3.14,0.02,-3.08);
	target_pose0.position.x = -0.10;
	target_pose0.position.y = -0.01;
	target_pose0.position.z =  0.12;
	group.setPoseTarget(target_pose0);

	// here we first check if we can find a plan
	moveit::planning_interface::MoveGroup::Plan plan0;
	bool success = group.plan(plan0);

	if (success)
	{
		group.move();
	}
	else
	{
		ROS_ERROR("Cannot find a valid plan...");
	}

	//OPEN GRIPPER
	ROS_INFO("Open Gripper");
	gripper.setJointValueTarget({gripper_open});
	gripper.move();
	ros::Duration(3).sleep(); // wait a few seconds here


	//GO TO PICKUP POS
	geometry_msgs::Pose target_pose1;
	target_pose1.orientation = tf::createQuaternionMsgFromRollPitchYaw(-3.14,1.54,-3.04);
	target_pose1.position.x = -0.14;
	target_pose1.position.y = -0.01;
	target_pose1.position.z = -0.04;
	group.setPoseTarget(target_pose1);

	// here we first check if we can find a plan
	moveit::planning_interface::MoveGroup::Plan plan1;
	success = group.plan(plan1);

	if (success)
	{
		group.move();
	}
	else
	{
		ROS_ERROR("Cannot find a valid plan...");
	}


	//CLOSE GRIPPER
	ROS_INFO("Close Gripper");
	gripper.setJointValueTarget({gripper_closed});
	gripper.move();

	ros::Duration(3).sleep(); // wait a few seconds here

	//GOING TO INIT POS
	group.setPoseTarget(target_pose0);

	// here we first check if we can find a plan
	moveit::planning_interface::MoveGroup::Plan plan2;
	success = group.plan(plan2);

	if (success)
	{
		group.move();
	}
	else
	{
		ROS_ERROR("Cannot find a valid plan...");
	}
	ROS_INFO("Pick completed. Waiting for user shutdown (ctrl-c).");
	ros::waitForShutdown();

	return 0;
}
