#include "ros/ros.h"

#include <tf/transform_listener.h>


int main(int argc, char **argv)
{

	ros::init(argc, argv, "tf_sub");
	ros::NodeHandle n;

	tf::TransformListener listener;

	ros::Time obj_ts = ros::Time::now();

	ros::Rate loop_rate(1);


	while (ros::ok())
	{
		tf::StampedTransform bf2odom;
		tf::StampedTransform odom2bf;
		tf::StampedTransform odom2obj;
		tf::StampedTransform obj2odom;

		tf::Transform bf2obj;
		tf::Transform obj2bf;

		try{
			listener.lookupTransform("/base_footprint", "/odom", ros::Time(0), bf2odom);
			ROS_INFO("/base_footprint -> /odom [%lf, %lf, %lf] %lf ago", bf2odom.getOrigin().x(), bf2odom.getOrigin().y(), bf2odom.getOrigin().z(), (ros::Time::now()-bf2odom.stamp_).toSec());
		}
		catch (tf::TransformException& ex){
			ROS_ERROR("%s",ex.what());
		}

		try{
			listener.lookupTransform("/odom", "/base_footprint", ros::Time(0), odom2bf);
			ROS_INFO("/odom -> /base_footprint  [%lf, %lf, %lf] %lf ago", odom2bf.getOrigin().x(), odom2bf.getOrigin().y(), odom2bf.getOrigin().z(), (ros::Time::now()-odom2bf.stamp_).toSec());
		}
		catch (tf::TransformException& ex){
			ROS_ERROR("%s",ex.what());
		}

		try{
			listener.lookupTransform("/odom", "/object", ros::Time(0), odom2obj);
			ROS_INFO("/odom -> /object [%lf, %lf, %lf] %lf ago", odom2obj.getOrigin().x(), odom2obj.getOrigin().y(), odom2obj.getOrigin().z(), (ros::Time::now()-odom2obj.stamp_).toSec());
		}
		catch (tf::TransformException& ex){
			ROS_ERROR("%s",ex.what());
		}

		try{
			listener.lookupTransform("/object", "/odom",  ros::Time(0), obj2odom);
			ROS_INFO("/object -> /odom  [%lf, %lf, %lf] %lf ago", obj2odom.getOrigin().x(), obj2odom.getOrigin().y(), obj2odom.getOrigin().z(), (ros::Time::now()-obj2odom.stamp_).toSec());
		}
		catch (tf::TransformException& ex){
			ROS_ERROR("%s",ex.what());
		}


		bf2obj = bf2odom * odom2obj;
		ROS_INFO("/base_footprint -> /object  [%lf, %lf, %lf] %lf ago", bf2obj.getOrigin().x(), bf2obj.getOrigin().y(), bf2obj.getOrigin().z(), (ros::Time::now()-odom2obj.stamp_).toSec());

		ROS_INFO("===========================================================================");

		ros::spinOnce();
		loop_rate.sleep();
	}

	return 0;

}
