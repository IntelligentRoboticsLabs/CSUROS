#include "ros/ros.h"

int main(int argc, char **argv)
{
   ros::init(argc, argv, "simple");
   ros::NodeHandle n;

   ros::spin();
   
   return 0;
 }
