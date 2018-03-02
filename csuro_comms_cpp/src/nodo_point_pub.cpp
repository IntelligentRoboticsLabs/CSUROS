#include "ros/ros.h"
#include "csuro_comms_cpp/Point.h"

int main(int argc, char **argv)
{

   ros::init(argc, argv, "point_publisher");
   ros::NodeHandle n;

   ros::Publisher point_pub = n.advertise<csuro_comms_cpp::Point>("/point", 1);

   ros::Rate loop_rate(10);

   while (ros::ok())
   {
	   csuro_comms_cpp::Point msg;

	   msg.x = 8.0;
	   msg.y = 9.0;
	   msg.z = 10.0;

	   point_pub.publish(msg);

	   ros::spinOnce();
	   loop_rate.sleep();
   }

   return 0;

 }
