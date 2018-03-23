#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int64.hpp"

rclcpp::Node::SharedPtr g_node = nullptr;

void messageCallback(const std_msgs::msg::Int64::SharedPtr msg)
{
  RCLCPP_INFO(g_node->get_logger(), "Data: '%ld'", msg->data);
}

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);

  g_node = rclcpp::Node::make_shared("num_subscriber");

  auto subscription = g_node->create_subscription<std_msgs::msg::Int64>
    ("topic", messageCallback);

  rclcpp::spin(g_node);
  rclcpp::shutdown();

  g_node = nullptr;

  return 0;
}
