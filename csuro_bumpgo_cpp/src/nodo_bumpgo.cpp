#include "ros/ros.h"

#include "kobuki_msgs/BumperEvent.h"
#include "geometry_msgs/Twist.h"

#define TURNING_TIME 5.0
#define BACKING_TIME 3.0

class BumpGo{
public:

	BumpGo(): state_(GOING_FORWARD), pressed_(false)
	{
		//sub_bumber_ = n_.subscribe(...);
		//pub_vel_ = n_.advertise<...>(...)
	}

	void bumperCallback(const kobuki_msgs::BumperEvent::ConstPtr& msg)
	{
		//pressed_ = (...);

		// ...
	}

	void step()
	{
		geometry_msgs::Twist cmd;

		switch(state_)
		{
		case GOING_FORWARD:
			//cmd.linear.x = ...;
			//cmd.angular.z = ...;
			if(pressed_)
			{
				press_ts_ = ros::Time::now();
				state_ = GOING_BACK;
				ROS_INFO("GOING_FORWARD -> GOING_BACK");
			}
			break;

		case GOING_BACK:
			//cmd.linear.x = ...;
			//cmd.angular.z = ...;

			if((ros::Time::now()-press_ts_).toSec() > BACKING_TIME )
			{
				turn_ts_ = ros::Time::now();
				state_ = TURNING;
				ROS_INFO("GOING_BACK -> TURNING");
			}
			break;

		case TURNING:
			//cmd.linear.x = ...;
			//cmd.angular.z = ...;
			if((ros::Time::now()-turn_ts_).toSec() > TURNING_TIME )
			{
				state_ = GOING_FORWARD;
				ROS_INFO("TURNING -> GOING_FORWARD");

			}
			break;
		}

		//pub_vel_.publish(...);
	}

private:
	ros::NodeHandle n_;

	static const int GOING_FORWARD 	= 0;
	static const int GOING_BACK 	= 1;
	static const int TURNING 		= 2;

	int state_;

	bool pressed_;

	ros::Time press_ts_;
	ros::Time turn_ts_;

	ros::Subscriber sub_bumber_;
	ros::Publisher pub_vel_;
};


int main(int argc, char **argv)
{

	ros::init(argc, argv, "bumpgo");

	BumpGo bumpgo;

	ros::Rate loop_rate(20);

	while (ros::ok())
	{
		bumpgo.step();

		ros::spinOnce();
		loop_rate.sleep();
	}



	return 0;

}
