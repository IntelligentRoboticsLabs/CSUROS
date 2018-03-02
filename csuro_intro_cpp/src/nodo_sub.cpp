#include "ros/ros.h"
#include "std_msgs/Int64.h"
#include "kobuki_msgs/BumperEvent.h"
#include "geometry_msgs/Twist.h"

geometry_msgs::Twist vel;

void messageCallback(const kobuki_msgs::BumperEvent::ConstPtr& msg)
{
  ROS_INFO("Bumper: [%d]", msg->bumper);
  ROS_INFO("State: [%d]", msg->state);


  if(msg->state == 0){
    vel.linear.x=0;
  }else{
    vel.linear.x=0.15;
  }


}

int main(int argc, char **argv)
{

   ros::init(argc, argv, "num_subscriber");
   ros::NodeHandle n;

   ros::Subscriber sub = n.subscribe("/mobile_base/events/bumper", 1, messageCallback);
   ros::Publisher num_pub = n.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1);

   ros::Rate loop_rate(10);

   while (ros::ok())
   {
     num_pub.publish(vel);
     ros::spinOnce();
     loop_rate.sleep();
   }

   return 0;

 }
