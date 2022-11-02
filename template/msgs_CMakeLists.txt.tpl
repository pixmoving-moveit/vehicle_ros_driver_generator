cmake_minimum_required(VERSION 3.0.2)
project(pix_%(car_type)s_driver_msgs)

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
  %(canID_msg_list)s
)

generate_messages(
  DEPENDENCIES
  std_msgs
  pix_%(car_type)s_driver_msgs
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
