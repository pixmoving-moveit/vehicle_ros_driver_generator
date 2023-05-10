#include <pix_%(car_type)s_driver/control_command.hpp>

namespace pix_%(car_type)s_driver
{
namespace control_command
{
ControlCommand::ControlCommand() : Node("control_command")
{
  // ros params
  param_.base_frame_id = declare_parameter("base_frame_id", "base_link");
  param_.command_timeout_ms = declare_parameter("command_timeout_ms", 1000);
  param_.loop_rate = declare_parameter("loop_rate", 50.0);

  // initialize msg received time, make reservation of data size
  // example brake_command_received_time_ = this->now();
  %(msg_reveived_timestamp_instance_list)s

  is_engage_ = true;

  using std::placeholders::_1;

  /* subscriber */
  {
    // from %(car_type)s driver autoware interface
    /**
    a2v_brake_ctrl_sub_ = create_subscription<A2vBrakeCtrl>(
      "/pix_hooke/a2v_brakectrl_131", 1, std::bind(&ControlCommand::callbackBrakeCtrl, this, _1));
    **/
    %(subscribe_instance_list)s
    // engage
    engage_ctrl_sub_ = create_subscription<std_msgs::msg::Bool>(
      "input/engage", 1, std::bind(&ControlCommand::callbackEngage, this, _1));
  }
  /* publisher */
  {
    // to socketcan drivier
    can_frame_pub_ = create_publisher<can_msgs::msg::Frame>("output/can_tx", rclcpp::QoS{1});
  }
  {
    // timer
    timer_ = rclcpp::create_timer(
      this, get_clock(), rclcpp::Rate(param_.loop_rate).period(),
      std::bind(&ControlCommand::timerCallback, this));
  }
}

// calback functions
/** example
void ControlCommand::callbackBrakeCtrl(const A2vBrakeCtrl::ConstSharedPtr & msg)
{
  brake_command_received_time_ = this->now();
  brake_ctrl_ptr_ = msg;
  a2v_brakectrl_131_entity_.Reset();
  a2v_brakectrl_131_entity_.UpdateData(
    msg->acu_chassis_brake_en, msg->acu_chassis_aeb_ctrl, msg->acu_chassis_brake_pdl_target,
    msg->acu_chassis_epb_ctrl, msg->acu_brake_life_sig, msg->acu_check_sum_131);
  can_msgs::msg::Frame brake_ctrl_can_msg;
  brake_ctrl_can_msg.header.stamp = msg->header.stamp;
  brake_ctrl_can_msg.dlc = 8;
  brake_ctrl_can_msg.id = a2v_brakectrl_131_entity_.ID;
  brake_ctrl_can_msg.is_extended = false;
  uint8_t *signal_bits;
  signal_bits = a2v_brakectrl_131_entity_.get_data();
  for (int i = 0; i < 8; i++)
  {
    brake_ctrl_can_msg.data[i] = *signal_bits;
    signal_bits += 1;
  }
  brake_ctrl_can_ptr_ = std::make_shared<can_msgs::msg::Frame>(brake_ctrl_can_msg);
}
**/
%(callback_functions_list)s

void ControlCommand::callbackEngage(const std_msgs::msg::Bool::ConstSharedPtr & msg)
{
  is_engage_ = msg->data;
}

void ControlCommand::timerCallback()
{
  if (!is_engage_) return;
  const rclcpp::Time current_time = this->now();

  // publishing msg
  /** example
  // brake control command 
  const double brake_command_delta_time_ms =
    (current_time - brake_command_received_time_).seconds() * 1000.0;
  if (brake_command_delta_time_ms > param_.command_timeout_ms || brake_ctrl_can_ptr_==nullptr) {
    RCLCPP_ERROR_THROTTLE(
      get_logger(), *this->get_clock(), std::chrono::milliseconds(5000).count(),
      "brake command timeout = %%f ms.", brake_command_delta_time_ms);
  } else {
    can_frame_pub_->publish(*brake_ctrl_can_ptr_);
  }
  **/
  %(publishing_msg_code_list)s
}

} // namespace control_command
} // namespace pix_%(car_type)s_driver
