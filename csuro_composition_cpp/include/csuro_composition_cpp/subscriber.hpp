#ifndef CSURO_COMPOSITION__SUBSCRIBER_NODE_HPP_
#define CSURO_COMPOSITION__SUBSCRIBER_NODE_HPP_

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int64.hpp"

class Subscriber : public rclcpp::Node
{
public:
  Subscriber();

private:

  void messageCallback(const std_msgs::msg::Int64::SharedPtr msg);

  rclcpp::Subscription<std_msgs::msg::Int64>::SharedPtr subscription_;
};


#endif
