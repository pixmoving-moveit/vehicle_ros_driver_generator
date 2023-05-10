#include <pix_%(car_type)s_driver/report_parser.hpp>

namespace pix_%(car_type)s_driver
{
namespace report_parser
{
ReportParser::ReportParser() : Node("report_parser")
{
  // ros params
  param_.base_frame_id = declare_parameter("base_frame_id", "base_link");
  param_.report_timeout_ms = declare_parameter("report_timeout_ms", 1000);
  param_.loop_rate = declare_parameter("loop_rate", 50.0);

  // // initialize msg received time
  /** example
  brake_command_received_time_ = this->now();
  **/
  %(msg_reveived_timestamp_instance_list)s

  is_publish_ = true;

  using std::placeholders::_1;

  /* subscriber */
  {
    // from pix driver autoware interface
    can_frame_sub_ = create_subscription<can_msgs::msg::Frame>(
      "input/can_rx", 1, std::bind(&ReportParser::callbackCan, this, _1));
    // is publish
    is_publish_sub_ = create_subscription<std_msgs::msg::Bool>(
      "input/is_publish", 1, std::bind(&ReportParser::callbackIsPublish, this, _1));
  }

  /* publisher */
  {
    /** example
    brake_sta_fb_pub_ =
      create_publisher<V2aBrakeStaFb>("/pix_hooke/v2a_brakestafb", rclcpp::QoS{1});
    **/
    %(publisher_instance_list)s 
  }
  {
    // timer
    timer_ = rclcpp::create_timer(
      this, get_clock(), rclcpp::Rate(param_.loop_rate).period(),
      std::bind(&ReportParser::timerCallback, this));
  }
}

// calback is publish
void ReportParser::callbackIsPublish(const std_msgs::msg::Bool::ConstSharedPtr & msg)
{
  is_publish_ = msg->data;
}

// callback can
void ReportParser::callbackCan(const can_msgs::msg::Frame::ConstSharedPtr & msg)
{
  std_msgs::msg::Header header;
  header.frame_id = param_.base_frame_id;
  header.stamp = msg->header.stamp;

  /** example
  V2aBrakeStaFb brake_sta_fb_msg;
  **/
  %(report_msg_list)s

  uint8_t byte_temp[8];
  switch (msg->id)
  {
  /** example
  case V2adrivestafb530::ID:
    drive_sta_fb_received_time_ = this->now();
    
    for(uint i=0;i<8;i++)
    {
    byte_temp[i] = msg->data[i];
    }
    v2a_drivestafb_530_entity_.update_bytes(byte_temp);
    v2a_drivestafb_530_entity_.Parse();

    drive_sta_fb_msg.header = header;
    drive_sta_fb_msg.vcu_chassis_driver_en_sta =
      v2a_drivestafb_530_entity_.vcu_chassisdriverensta;
    drive_sta_fb_msg.vcu_chassis_diver_slopover =
      v2a_drivestafb_530_entity_.vcu_chassisdiverslopover;
    drive_sta_fb_msg.vcu_chassis_driver_mode_sta =
      v2a_drivestafb_530_entity_.vcu_chassisdrivermodesta;
    drive_sta_fb_msg.vcu_chassis_gear_fb = v2a_drivestafb_530_entity_.vcu_chassisgearfb;
    drive_sta_fb_msg.vcu_chassis_speed_fb = v2a_drivestafb_530_entity_.vcu_chassisspeedfb;
    drive_sta_fb_msg.vcu_chassis_throttle_padl_fb =
      v2a_drivestafb_530_entity_.vcu_chassisthrottlepaldfb;
    drive_sta_fb_msg.vcu_chassis_accceleration_fb =
      v2a_drivestafb_530_entity_.vcu_chassisaccelerationfb;
    drive_sta_fb_ptr_ = std::make_shared<V2aDriveStaFb>(drive_sta_fb_msg);
    break;
  **/
  %(parser_case_code_list)s

  default:
    break;
  }
}

void ReportParser::timerCallback()
{
  if (!is_publish_) return;

  const rclcpp::Time current_time = this->now();
  
  /** example
  // drive sta fb report
  const double drive_sta_fb_report_delta_time_ms =
    (current_time - drive_sta_fb_received_time_).seconds() * 1000.0;
  if(drive_sta_fb_report_delta_time_ms>param_.report_timeout_ms || drive_sta_fb_ptr_==nullptr)
  {
    RCLCPP_ERROR_THROTTLE(
      get_logger(), *this->get_clock(), std::chrono::milliseconds(5000).count(),
      "drive stat fb report timeout = %%f ms.", drive_sta_fb_report_delta_time_ms);
  }else{
    drive_sta_fb_pub_->publish(*drive_sta_fb_ptr_);
  }
  **/
  %(report_msg_code_list)s
  
}

} // namespace report_parser
} // namespace pix_%(car_type)s_driver
