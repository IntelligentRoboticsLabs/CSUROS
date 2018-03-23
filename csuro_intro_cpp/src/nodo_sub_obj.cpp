#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int64.hpp"

using std::placeholders::_1;

class Listener : public rclcpp::Node
{
public:
	Listener(): Node("num_subscriber")
	{
        sub_ = create_subscription<std_msgs::msg::Int64>("topic",
            std::bind(&Listener::messageCallback, this, _1));
	}

	void messageCallback(const std_msgs::msg::Int64::SharedPtr msg)
	{
		 RCLCPP_INFO(this->get_logger(), "Data: '%ld'", msg->data);
	}

private:
    rclcpp::Subscription<std_msgs::msg::Int64>::SharedPtr sub_;

};

int main(int argc, char **argv)
{

   rclcpp::init(argc, argv);

   auto node = std::make_shared<Listener>();

   rclcpp::spin(node);

   rclcpp::shutdown();
   return 0;

 }
