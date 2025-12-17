#pragma once

#include <string>
#include <memory>

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/bool.hpp>
#include <can_msgs/msg/frame.hpp>
#include <diagnostic_updater/diagnostic_updater.hpp>

// pix_%(car_type)s_driver msgs - include_msgsName_list
%(include_msgsName_list)s

// pix_%(car_type)s_driver parse  - include_ParseName_list
%(include_ParseName_list)s

#define ERROR_THRESHOLD 5   // 严重级别延迟阈值
#define WARNING_THRESHOLD 3  // 警告级别延迟阈值
// 延迟记录
struct DelayRecording
{
  uint32_t count_eorro;  // 严重级别延迟累计 - 丢失5个周期
  uint32_t count_waring; // 警告级别延迟累计 - 丢失3个周期
};

namespace pix_%(car_type)s_driver
{
namespace control_command
{

/**
 * @param pix_interface_driver_eorro pix_interface 严重超时阀值
 * @param pix_interface_driver_warn pix_interface 警告超时阀值
 */
struct TimeoutThresholdMs
{
  uint8_t pix_interface_driver_eorro;  // ms
  uint8_t pix_interface_driver_warn;  // ms
};

/**
 * @brief param structure of control command node
 * @param base_frame_id frame id of vehicle
 * @param loop_rate loop rate of publishers in hz
 * @param timeout_threshold_ms 超时阀值
 */
struct Param
{
  std::string base_frame_id;
  double loop_rate;
  TimeoutThresholdMs timeout_threshold_ms;
};

class ControlCommand : public rclcpp::Node
{
private:
  // Diagnostics Updater
  diagnostic_updater::Updater updater_;
  void onDelayedAlarm(diagnostic_updater::DiagnosticStatusWrapper & stat);

  // 订阅 pix_interface 底盘控制帧的下发延迟记录 - delay_recording_definition_list
%(delay_recording_definition_list)s

  // 订阅 pix_interface 是否已经下发 - is_pix_interface_definition_list
%(is_pix_interface_definition_list)s

private:
  // parameters of node
  Param param_;

  // subscribers - subscriber_member_list
%(subscriber_member_list)s

  // pix_%(car_type)s_driver msgs -  msg_member_list
%(msg_member_list)s

  // control command structures - control_command_structure_list
%(control_command_structure_list)s

  // msg received timestamp - msg_received_timestamp_list
%(msg_received_timestamp_list)s

  // publishers to can card driver
  rclcpp::Publisher<can_msgs::msg::Frame>::SharedPtr can_frame_pub_;

  // publishing can msgs - publishing_can_msg_list
  %(publishing_can_msg_list)s

  // timer
  rclcpp::TimerBase::SharedPtr timer_;

public:
  ControlCommand(const rclcpp::NodeOptions & node_option);

  // calback functions - callback_function_prototype_list
%(callback_function_prototype_list)s
  void timerCallback();

};

} // control_command
} // pix_%(car_type)s_driver