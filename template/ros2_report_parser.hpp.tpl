#pragma once

#include <string>
#include <memory>

#include <rclcpp/rclcpp.hpp>

#include <std_msgs/msg/bool.hpp>
#include <std_msgs/msg/header.hpp>

#include <can_msgs/msg/frame.hpp>


// pix_%(car_type)s_driver_msgs - include_msg_list
%(include_msg_list)s

// protocol libs - include_hpp_list
%(include_hpp_list)s

namespace pix_%(car_type)s_driver
{
namespace report_parser
{

/**
 * @brief param structure of report parser node
 * @param base_frame_id frame id of vehicle
 * @param loop_rate loop rate of publishers in hz
 */
struct Param
{
  std::string base_frame_id;
  double loop_rate;
};

class ReportParser : public rclcpp::Node
{
private:
  // parameters of node
  Param param_;

  // subscribers from socketcan interface
  rclcpp::Subscription<can_msgs::msg::Frame>::SharedPtr can_frame_sub_;

  // publishers - publisher_list
%(publisher_list)s

  // can frame entities - publisher_msg_list
%(publisher_msg_list)s
  
public:
  ReportParser(const rclcpp::NodeOptions & node_option);

  // callback
  /// @brief callback function of can Frame msgs, to store the data to member variable
  void callbackCan(const can_msgs::msg::Frame::ConstSharedPtr & msg);
};
} // report_parser
} // pix_%(car_type)s_driver