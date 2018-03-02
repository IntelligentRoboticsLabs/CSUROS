#include "ros/ros.h"
#include <iostream>

#include <visualization_msgs/MarkerArray.h>
#include <visualization_msgs/Marker.h>

int main(int argc, char **argv)
{

   ros::init(argc, argv, "iterativo");
   ros::NodeHandle n;

   ros::Rate loop_rate(20);

   ros::Publisher arrows_pub = n.advertise<visualization_msgs::MarkerArray>("/arrows", 1, true);

   visualization_msgs::MarkerArray arrows;
   visualization_msgs::Marker arrow1;
   visualization_msgs::Marker arrow2;

   int count=0;

   while (ros::ok())
   {

	   arrow1.header.frame_id = "base_footprint";
	   arrow1.header.stamp = ros::Time();
	   arrow1.type = visualization_msgs::Marker::ARROW;
	   arrow1.action = visualization_msgs::Marker::ADD;
	   arrow1.pose.position.x = 0.0;
	   arrow1.pose.position.y = 0.0;
	   arrow1.pose.position.z = 0.0;
	   arrow1.pose.orientation.x = 0.0;
	   arrow1.pose.orientation.y = 0.0;
	   arrow1.pose.orientation.z = 0.0;
	   arrow1.pose.orientation.w = 1.0;
	   arrow1.scale.x = 0.5;
	   arrow1.scale.y = 0.01;
	   arrow1.scale.z = 0.01;
	   arrow1.color.a = 1.0;
	   arrow1.color.r = 1.0;
	   arrow1.color.g = 0.0;
	   arrow1.color.b = 0.0;

	   arrow2.header.frame_id = "base_footprint";
	   arrow2.header.stamp = ros::Time();
	   arrow2.type = visualization_msgs::Marker::ARROW;
	   arrow2.action = visualization_msgs::Marker::ADD;
	   arrow2.pose.position.x = 0.0;
	   arrow2.pose.position.y = 0.0;
	   arrow2.pose.position.z = 0.0;
	   arrow2.pose.orientation.x = 0.0;
	   arrow2.pose.orientation.y = 1.0;
	   arrow2.pose.orientation.z = 0.0;
	   arrow2.pose.orientation.w = 1.0;
	   arrow2.scale.x = 0.5;
	   arrow2.scale.y = 0.01;
	   arrow2.scale.z = 0.01;
	   arrow2.color.a = 1.0;
	   arrow2.color.r = 0.0;
	   arrow2.color.g = 1.0;
	   arrow2.color.b = 0.0;

	   arrows.markers.push_back(arrow1);
	   arrows.markers.push_back(arrow2);

	   arrows_pub.publish(arrows);



     ros::spinOnce();
     loop_rate.sleep();
   }

   return 0;

 }
