#include <pix_%(car_type)s_driver/control_command.hpp>

namespace pix_%(car_type)s_driver
{
namespace control_command
{
ControlCommand::ControlCommand(const rclcpp::NodeOptions & node_options) 
: Node("control_command", node_options),
updater_(this)
{
  // init delay_recording_init_list is_pix_interface_init_list
%(delay_recording_init_list)s
%(is_pix_interface_init_list)s

  float pix_interface_driver_period_ms =
    declare_parameter("pix_interface_driver_period_ms", 50.0);
  param_.timeout_threshold_ms.pix_interface_driver_eorro  = pix_interface_driver_period_ms*ERROR_THRESHOLD;
  param_.timeout_threshold_ms.pix_interface_driver_warn  = pix_interface_driver_period_ms*WARNING_THRESHOLD;

  // ros params
  param_.base_frame_id = declare_parameter("base_frame_id", "base_link");
  param_.loop_rate = declare_parameter("loop_rate", 50.0);

  // initialize msg received time, make reservation of data size - msg_reveived_timestamp_instance_list
%(msg_reveived_timestamp_instance_list)s

  using std::placeholders::_1;

  // Diagnostics Updater
  updater_.setHardwareID("pix_robobus_driver-ControlCommand");
  updater_.add("delayed_alarm", this, &ControlCommand::onDelayedAlarm);

  /* subscriber */
  {
    // from %(car_type)s driver autoware interface - subscribe_instance_list
  %(subscribe_instance_list)s
  }

  /* publisher */
  {
    // to socketcan drivier
    can_frame_pub_ = create_publisher<can_msgs::msg::Frame>("output/can_tx", rclcpp::QoS{500});
  }

  {
    // timer
    timer_ = rclcpp::create_timer(
      this, get_clock(), rclcpp::Rate(param_.loop_rate).period(),
      std::bind(&ControlCommand::timerCallback, this));
  }
}

// calback functions -- callback_functions_list
%(callback_functions_list)s

void ControlCommand::onDelayedAlarm(diagnostic_updater::DiagnosticStatusWrapper & stat)
{
  const std::string error_msg = "[ReportConverter]: Timeout";
  const auto diag_level = diagnostic_msgs::msg::DiagnosticStatus::OK;
  stat.summary(diag_level, error_msg);
  // on_delayed_alarm_list
  %(on_delayed_alarm_list)s
}

void ControlCommand::timerCallback()
{

  // 如果存在一个为flase，表示初始化没有下发 - if_pix_interface_definition_list
%(if_pix_interface_definition_list)s
  const rclcpp::Time current_time = this->now();
  // if_msg_received_timestamp_list
%(if_msg_received_timestamp_list)s
}

} // namespace control_command
} // namespace pix_%(car_type)s_driver
#include "rclcpp_components/register_node_macro.hpp"
RCLCPP_COMPONENTS_REGISTER_NODE(pix_robobus_driver::control_command::ControlCommand)