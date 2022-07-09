cmake_minimum_required(VERSION 3.0.2)
project(pix_driver_msgs)

find_package(catkin REQUIRED COMPONENTS
  message_generation
  message_runtime
  roscpp
  std_msgs
)

file(GLOB MSGS_PATH ./mgs/*.msg)

# GearReport.msg
# {name}.msg
add_message_files(
  FILES
  	vcu2acu_chassiserrcode1_200.msg
	vcu2acu_chassiserrcode2_201.msg
	vcu2acu_chassiserrcode3_202.msg
	throttle_report_500.msg
	brake_report_501.msg
	steering_report_502.msg
	gear_report_503.msg
	park_report_504.msg
	vcu_report_505.msg
	wheelspeed_report_506.msg
	bms_report_512.msg
	vcu2acu_sweepstafb_517.msg
	vcu2acu_sweepfansta_518.msg
	vcu2acu_sweepsta_519.msg
	vcu2acu_sweepweedingsta_520.msg
	vcu2acu_sweepworksta_521.msg
	throttle_command_100.msg
	brake_command_101.msg
	steering_command_102.msg
	gear_command_103.msg
	park_command_104.msg
	vehicle_mode_command_105.msg
	acu_sweepctrlcmd_107.msg

)

generate_messages(
  DEPENDENCIES
  std_msgs
  pix_driver_msgs
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES pix_driver_msg
#  CATKIN_DEPENDS message_generation message_runtime roscpp std_msgs
#  DEPENDS system_lib
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)
