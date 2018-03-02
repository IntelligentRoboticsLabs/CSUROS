/*
 * Scan.h
 *
 *  Created on: 24/12/2015
 *      Author: paco
 */

#ifndef SCAN_H_
#define SCAN_H_

#include "ros/ros.h"

#include <sensor_msgs/LaserScan.h>
#include <tf/transform_listener.h>
#include <tf/message_filter.h>
#include <message_filters/subscriber.h>
#include <tf/tf.h>

class Scan {
public:
	Scan();
	virtual ~Scan();

	void scanCallback(const sensor_msgs::LaserScan::ConstPtr& scan_in);

	const std::vector<tf::Stamped<tf::Point> >& getLastScan() const {return scan_bf_;};

private:
	ros::NodeHandle nh_;

	std::string baseFrameId_;
	std::string laser_topic_;

	tf::TransformListener tfListener_;

	std::vector<tf::Stamped<tf::Point> > scan_bf_;
	double robot_radious_;

	tf::MessageFilter<sensor_msgs::LaserScan>* tfScanSub_;
	message_filters::Subscriber<sensor_msgs::LaserScan>* scanSub_;

};

#endif /* SCAN_H_ */
