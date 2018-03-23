#include <memory>
#include "csuro_composition_cpp/subscriber.hpp"
#include "csuro_composition_cpp/publisher.hpp"
#include "rclcpp/rclcpp.hpp"

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::executors::SingleThreadedExecutor exec;
  auto publisher_node = std::make_shared<Publisher>();
  auto subscriber_node = std::make_shared<Subscriber>();
  exec.add_node(publisher_node);
  exec.add_node(subscriber_node);
  exec.spin();
  rclcpp::shutdown();
  return 0;
}
