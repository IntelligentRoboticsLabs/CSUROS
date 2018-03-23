#include <chrono>

#include "csuro_composition_cpp/subscriber.hpp"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int64.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;

Subscriber::Subscriber()
: Node("subscriber_node")
{
    subscription_ = create_subscription<std_msgs::msg::Int64>("topic",
        std::bind(&Subscriber::messageCallback, this, _1));
}

void
Subscriber::messageCallback(const std_msgs::msg::Int64::SharedPtr msg)
{
     RCLCPP_INFO(this->get_logger(), "Data: '%ld'", msg->data);
}

#include "class_loader/class_loader_register_macro.h"
CLASS_LOADER_REGISTER_CLASS(Subscriber, rclcpp::Node)
