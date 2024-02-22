#include <chrono>
#include <cinttypes>
#include <cstdio>
#include <memory>
#include <string>
#include <utility>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"

using namespace std::chrono_literals;

namespace TestPkg {

// Node that consumes messages.
struct Consumer : public rclcpp::Node
{
  Consumer(const rclcpp::NodeOptions & options)
  : Node("Consumer", options)
  {
    // Create a subscription on the input topic which prints on receipt of new messages.
    sub_ = this->create_subscription<std_msgs::msg::Int32>(
      "number",
      10,
      [this](const std_msgs::msg::Int32::UniquePtr msg) {
        RCLCPP_INFO(get_logger(),
          " Received message with value: %d, and address: 0x%" PRIXPTR "", msg->data,
          reinterpret_cast<std::uintptr_t>(&(msg->data)));
      });
  }

  rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr sub_;
};

}

#include "rclcpp_components/register_node_macro.hpp"
RCLCPP_COMPONENTS_REGISTER_NODE(TestPkg::Consumer)