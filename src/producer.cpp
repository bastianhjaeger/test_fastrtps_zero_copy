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

// Node that produces messages.
struct Producer : public rclcpp::Node
{
  Producer(const rclcpp::NodeOptions & options)
  : Node("Producer", options)
  {
    // Create a publisher on the output topic.
    pub_ = this->create_publisher<std_msgs::msg::Int32>("number", 10);
    std::weak_ptr<std::remove_pointer<decltype(pub_.get())>::type> captured_pub = pub_;
    // Create a timer which publishes on the output topic at ~1Hz.
    auto callback = [this, options, captured_pub]() -> void {
        auto pub_ptr = captured_pub.lock();
        if (!pub_ptr) {
          return;
        }

        static int32_t count = 0;
        if ( options.use_intra_process_comms() ) {
          std_msgs::msg::Int32::UniquePtr msg(new std_msgs::msg::Int32());
          msg->data = count++;
          RCLCPP_INFO(get_logger(),
            "Published message with value: %d, and address: 0x%" PRIXPTR "", msg->data,
            reinterpret_cast<std::uintptr_t>(&(msg->data)));
          pub_ptr->publish(std::move(msg));
        }
        else {
          auto msg = pub_ptr->borrow_loaned_message();
          msg.get().data = count++;
          RCLCPP_INFO(get_logger(),
            "Publ loan message with value: %d, and address: 0x%" PRIXPTR "", msg.get().data,
            reinterpret_cast<std::uintptr_t>(&(msg.get().data)));
          pub_ptr->publish(std::move(msg));
        }
      };
    timer_ = this->create_wall_timer(1s, callback);
  }

  rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr pub_;
  rclcpp::TimerBase::SharedPtr timer_;
};

}

#include "rclcpp_components/register_node_macro.hpp"
RCLCPP_COMPONENTS_REGISTER_NODE(TestPkg::Producer)