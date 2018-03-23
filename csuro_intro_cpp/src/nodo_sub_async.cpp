#include "ros/ros.h"
#include "std_msgs/Int64.h"

void messageCallback(const std_msgs::Int64::ConstPtr& msg)
{
  ROS_INFO("Message: [%ld]", msg->data);
}

int main(int argc, char **argv)
{
	 ros::init(argc, argv, "num_subscriber");
   ros::NodeHandle n;

	 ros::Rate loop_rate(20);

	 ros::AsyncSpinner spinner(1);
	 spinner.start();

   ros::Subscriber sub = n.subscribe("message", 1, messageCallback);

   while(ros::ok())
	 {
		 ROS_INFO("Main");
		 loop_rate.sleep();
	 }

   return 0;

 }
