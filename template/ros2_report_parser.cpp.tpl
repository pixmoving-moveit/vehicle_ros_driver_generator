#include <pix_%(car_type)s_driver/report_parser.hpp>

namespace pix_%(car_type)s_driver
{
namespace report_parser
{
ReportParser::ReportParser(const rclcpp::NodeOptions & node_option) 
: Node("report_parser", node_option)
{
  // ros params
  param_.base_frame_id = declare_parameter("base_frame_id", "base_link");
  param_.loop_rate = declare_parameter("loop_rate", 50.0);

  using std::placeholders::_1;

  /* subscriber */
  {
    // from pix driver autoware interface
    can_frame_sub_ = create_subscription<can_msgs::msg::Frame>(
      "input/can_rx", 500, std::bind(&ReportParser::callbackCan, this, _1));
  }

  /* publisher - publisher_instance_list*/
  {
%(publisher_instance_list)s 
  }
}

// callback can
void ReportParser::callbackCan(const can_msgs::msg::Frame::ConstSharedPtr & msg)
{
  std_msgs::msg::Header header;
  header.frame_id = param_.base_frame_id;
  header.stamp = msg->header.stamp;

  // pix_msg  - report_msg_list
%(report_msg_list)s

  // can - parser_case_code_list
  uint8_t byte_temp[8];
  switch (msg->id)
  {
%(parser_case_code_list)s
  default:
    break;
  }
}

} // namespace report_parser
} // namespace pix_%(car_type)s_driver
#include "rclcpp_components/register_node_macro.hpp"
RCLCPP_COMPONENTS_REGISTER_NODE(pix_robobus_driver::report_parser::ReportParser)