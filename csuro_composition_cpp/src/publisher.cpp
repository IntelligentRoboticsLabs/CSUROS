#include <chrono>

#include "csuro_composition_cpp/publisher.hpp"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int64.hpp"

using namespace std::chrono_literals;

Publisher::Publisher()
: Node("publisher_node"), count_(0)
{
    publisher_ = create_publisher<std_msgs::msg::Int64>("topic");
    timer_ = create_wall_timer(500ms, std::bind(&Publisher::on_timer, this));
}

void Publisher::on_timer()
{
  auto message = std_msgs::msg::Int64();
  message.data = count_++;
  RCLCPP_INFO(this->get_logger(), "Publisher: '%d'", count_)
  publisher_->publish(message);
}

#include "class_loader/class_loader_register_macro.h"
CLASS_LOADER_REGISTER_CLASS(Publisher, rclcpp::Node)
