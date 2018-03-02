#include "ros/ros.h"
#include "std_msgs/Int64.h"

int main(int argc, char **argv)
{

   ros::init(argc, argv, "num_publisher");
   ros::NodeHandle n;

   ros::Publisher num_pub = n.advertise<std_msgs::Int64>("/message", 1);

   ros::Rate loop_rate(10);

   int count=0;

   while (ros::ok())
   {

     std_msgs::Int64 msg;
     msg.data = count++;

     num_pub.publish(msg);

     ros::spinOnce();
     loop_rate.sleep();
   }

   return 0;

 }
