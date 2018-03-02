#include "ros/ros.h"
#include "std_msgs/Int64.h"

class Listener
{
public:
	Listener(): n_()
	{
		sub_ = n_.subscribe("message", 1, &Listener::messageCallback, this);
	}

	void messageCallback(const std_msgs::Int64::ConstPtr& msg)
	{
		ROS_INFO("Message: [%ld]", msg->data);
	}

private:
	ros::NodeHandle n_;
	ros::Subscriber sub_;
};

int main(int argc, char **argv)
{

   ros::init(argc, argv, "num_subscriber");
   ros::NodeHandle n;

   Listener listener;

   ros::spin();

   return 0;

 }
