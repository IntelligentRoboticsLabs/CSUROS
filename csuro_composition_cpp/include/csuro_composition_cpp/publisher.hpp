#ifndef CSURO_COMPOSITION__PUBLISHER_NODE_HPP_
#define CSURO_COMPOSITION__PUBLISHER_NODE_HPP_

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int64.hpp"

class Publisher : public rclcpp::Node
{
public:
  Publisher();

private:

  void on_timer();

  int count_;
  rclcpp::Publisher<std_msgs::msg::Int64>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
};


#endif
