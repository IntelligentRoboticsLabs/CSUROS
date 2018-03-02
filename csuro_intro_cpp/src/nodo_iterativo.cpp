#include "ros/ros.h"

int main(int argc, char **argv)
{

   ros::init(argc, argv, "iterativo");
   ros::NodeHandle n;

   ros::Rate loop_rate(20);

   int count=0;

   while (ros::ok())
   {
     ROS_INFO("iteration %d", count++);

     ros::spinOnce();
     loop_rate.sleep();
   }

   return 0;

 }
