cmake_minimum_required(VERSION 3.0.2)
project(pix_driver)

find_package(catkin REQUIRED COMPONENTS
  autoware_msgs
  can_msgs
  roscpp
  std_msgs
  pix_driver_msgs
)

catkin_package(
 INCLUDE_DIRS include
 LIBRARIES pix_driver
 CATKIN_DEPENDS autoware_msgs can_msgs roscpp std_msgs pix_driver_msgs
# DEPENDS system_lib
)

include_directories(
 include
  ${catkin_INCLUDE_DIRS}
)

## Declare a C++ library
# add_library(${PROJECT_NAME}
#   src/${PROJECT_NAME}/pix_driver.cpp
# )

# src/steering_report_502.cc
# src/{name}.cc
add_executable(${PROJECT_NAME}_report_node 
src/vcu2acu_chassiserrcode1_200.cc
src/vcu2acu_chassiserrcode2_201.cc
src/vcu2acu_chassiserrcode3_202.cc
src/throttle_report_500.cc
src/brake_report_501.cc
src/steering_report_502.cc
src/gear_report_503.cc
src/park_report_504.cc
src/vcu_report_505.cc
src/wheelspeed_report_506.cc
src/bms_report_512.cc
src/vcu2acu_sweepstafb_517.cc
src/vcu2acu_sweepfansta_518.cc
src/vcu2acu_sweepsta_519.cc
src/vcu2acu_sweepweedingsta_520.cc
src/vcu2acu_sweepworksta_521.cc


src/report_node.cc
src/Byte.cc
)

# src/steering_command_102.cc
# src/{name}.cc
add_executable(${PROJECT_NAME}_command_node
src/throttle_command_100.cc
src/brake_command_101.cc
src/steering_command_102.cc
src/gear_command_103.cc
src/park_command_104.cc
src/vehicle_mode_command_105.cc
src/acu_sweepctrlcmd_107.cc


src/command_node.cc
src/Byte.cc
)


add_dependencies(${PROJECT_NAME}_report_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
add_dependencies(${PROJECT_NAME}_command_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Specify libraries to link a library or executable target against
target_link_libraries(${PROJECT_NAME}_report_node
  ${catkin_LIBRARIES}
)

target_link_libraries(${PROJECT_NAME}_command_node
  ${catkin_LIBRARIES}
)


install(TARGETS ${PROJECT_NAME}_report_node
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION}
)

install(TARGETS ${PROJECT_NAME}_command_node
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION}
)

