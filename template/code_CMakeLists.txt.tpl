cmake_minimum_required(VERSION 3.0.2)
project(pix_%(car_type)s_driver)

find_package(catkin REQUIRED COMPONENTS
  can_msgs
  roscpp
  std_msgs
  pix_%(car_type)s_driver_msgs
)

catkin_package(
 INCLUDE_DIRS include
 LIBRARIES pix_%(car_type)s_driver
 CATKIN_DEPENDS can_msgs roscpp std_msgs pix_%(car_type)s_driver_msgs
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
%(report_cpp_list)s

src/report_node.cc
src/Byte.cc
)

# src/steering_command_102.cc
# src/{name}.cc
add_executable(${PROJECT_NAME}_command_node
%(command_cpp_list)s

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
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(TARGETS ${PROJECT_NAME}_command_node
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

