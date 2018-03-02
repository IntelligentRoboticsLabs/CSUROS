#include "ros/ros.h"
#include "csuro_comms_cpp/Distance.h"

#include <math.h>

bool distance(csuro_comms_cpp::Distance::Request  &req,
         csuro_comms_cpp::Distance::Response &res)
{
  double comp_x, comp_y, comp_z;

  comp_x = req.a.x - req.b.x;
  comp_y = req.a.y - req.b.y;
  comp_z = req.a.z - req.b.z;
  
  res.distance = sqrt(comp_x*comp_x + comp_y*comp_y + comp_z*comp_z);
  
  ROS_INFO("request: a=(%lf, %lf, %lf), b=(%lf, %lf, %lf)", 
	req.a.x, req.a.y, req.a.z, req.b.x, req.b.y, req.b.z);
  ROS_INFO("sending back response: [%lf]", res.distance);
  return true;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "distance_server");
  ros::NodeHandle n;

  ros::ServiceServer service = n.advertiseService("distance", distance);
  ROS_INFO("Ready to calculate distances.");
  ros::spin();

  return 0;
}
