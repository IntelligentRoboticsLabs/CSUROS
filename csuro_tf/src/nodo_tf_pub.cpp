#include "ros/ros.h"
#include <time.h>
#include <math.h>

#include <tf/transform_broadcaster.h>

#define OBJ_PUB_RATE	10.0


void publishObj(tf::TransformBroadcaster& br)
{
	float x, y, z;
	float ax, ay, az;

	//generate a position in [10, -10] in base_footprint
	x = 20.0 * (rand()/static_cast<float>(RAND_MAX)) - 10.0;
	y = 20.0 * (rand()/static_cast<float>(RAND_MAX)) - 10.0;
	z = 0.0;
	ax = 0.0;
	ay = 0.0;
	az = 2.0*M_PI * (rand()/static_cast<float>(RAND_MAX)) - M_PI;

	tf::StampedTransform object;
	object.child_frame_id_ = "object";
	object.frame_id_ = "base_footprint";
	object.stamp_ = ros::Time::now();

	object.setOrigin(tf::Vector3(x,y,z));

	tf::Quaternion q;
	q.setRPY(ax, ay, az);
	object.setRotation(q);

	try {
		br.sendTransform(object);
	}
	catch(tf::TransformException &exception) {
		ROS_ERROR("%s", exception.what());
	}
}

int main(int argc, char **argv)
{

	ros::init(argc, argv, "tf_pub");
	ros::NodeHandle n;

	tf::TransformBroadcaster br;

	ros::Time obj_ts = ros::Time::now();

	ros::Rate loop_rate(20);

	srand (time(NULL));

	while (ros::ok())
	{

		if((ros::Time::now()-obj_ts).toSec() > OBJ_PUB_RATE)
		{
			obj_ts = ros::Time::now();
			publishObj(br);
		}

		ros::spinOnce();
		loop_rate.sleep();
	}

	return 0;

}
