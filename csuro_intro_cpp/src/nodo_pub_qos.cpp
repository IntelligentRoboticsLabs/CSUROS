#include "rclcpp/rclcpp.hpp"
#include <chrono>
#include "std_msgs/msg/int64.hpp"

using namespace std::chrono_literals;

int main(int argc, char **argv)
{

    rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("num_publisher");
    auto publisher = node->create_publisher<std_msgs::msg::Int64>("topic", rmw_qos_profile_sensor_data);
    auto message = std::make_shared<std_msgs::msg::Int64>();

    int count=0;

    rclcpp::WallRate loop_rate(50ms);

    while (rclcpp::ok())
    {
        message->data = count++;

        publisher->publish(message);

        rclcpp::spin_some(node);
        loop_rate.sleep();
    }

    rclcpp::shutdown();

    return 0;

 }
