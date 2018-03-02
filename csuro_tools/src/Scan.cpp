/*
 * Scan.cpp
 *
 *  Created on: 24/12/2015
 *      Author: paco
 */

#include "csuro_tools/Scan.h"

Scan::Scan()
: nh_(),
  baseFrameId_("base_footprint"),
  laser_topic_("/scan"),
  scan_bf_()
{
	scanSub_ = new message_filters::Subscriber<sensor_msgs::LaserScan> (nh_, laser_topic_, 5);
	tfScanSub_ = new tf::MessageFilter<sensor_msgs::LaserScan> (*scanSub_, tfListener_, baseFrameId_, 5);
	tfScanSub_->registerCallback(boost::bind(&Scan::scanCallback, this, _1));


}

Scan::~Scan() {
}


void
Scan::scanCallback(const sensor_msgs::LaserScan::ConstPtr& scan_in)
{
	float o_t_min, o_t_max, o_t_inc;

	o_t_min = scan_in->angle_min;
	o_t_max = scan_in->angle_max;
	o_t_inc = scan_in->angle_increment;

	int num_points = (int)2.0*o_t_max/o_t_inc;

	tf::Stamped<tf::Point> scan_sensor[num_points];
	scan_bf_.resize(num_points);

	float rx=0.0, ry=0.0;
	int c=0;

	for(int i=0; i<num_points; i++)
	{
		float theta = o_t_min+i*o_t_inc;
		float r = scan_in->ranges[i];

		scan_sensor[i].setX(r*cos(theta));
		scan_sensor[i].setY(r*sin(theta));
		scan_sensor[i].setZ(0.0);
		scan_sensor[i].setW(1.0);
		scan_sensor[i].stamp_ = scan_in->header.stamp;
		scan_sensor[i].frame_id_ = scan_in->header.frame_id;

		tfListener_.transformPoint(baseFrameId_, scan_sensor[i], scan_bf_[i]);
	}

}
