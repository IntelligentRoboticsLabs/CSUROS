#include "ros/ros.h"
#include <iostream>

#include "csuro_tools/Scan.h"

int main(int argc, char **argv)
{

   ros::init(argc, argv, "iterativo");
   ros::NodeHandle n;

   ros::Rate loop_rate(20);

   Scan scan;

   int count=0;

   while (ros::ok())
   {
     ROS_INFO("iteration %d", count++);

     std::vector<tf::Stamped<tf::Point> > last_scan = scan.getLastScan();

     if(last_scan.size()>0 && (last_scan.begin()->stamp_ - ros::Time::now()).toSec() < 1.0)
     {
    	 std::vector<tf::Stamped<tf::Point> >::iterator it;

    	 for(it=last_scan.begin(); it!=last_scan.end(); ++it)
    		 std::cout<<"("<<it->getX()<<", "<<it->getY()<<", "<<it->getZ()<<") ";

     }

     ros::spinOnce();
     loop_rate.sleep();
   }

   return 0;

 }
