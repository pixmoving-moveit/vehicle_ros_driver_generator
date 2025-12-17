cmake_minimum_required(VERSION 3.5)
project(pix_%(car_type)s_driver)

find_package(ament_cmake_auto REQUIRED)
ament_auto_find_build_dependencies()

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_CXX_EXTENSIONS OFF)
endif()
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

ament_auto_add_library(${PROJECT_NAME}_control_command SHARED
%(command_cpp_list)s
  src/libs/Byte.cc
  src/control_command.cpp
)

rclcpp_components_register_node(${PROJECT_NAME}_control_command
  PLUGIN "pix_%(car_type)s_driver::control_command::ControlCommand"
  EXECUTABLE ${PROJECT_NAME}_control_command_node
)

ament_auto_add_library(${PROJECT_NAME}_report_parser SHARED
%(report_cpp_list)s
  src/libs/Byte.cc
  src/report_parser.cpp
)

rclcpp_components_register_node(${PROJECT_NAME}_report_parser
  PLUGIN "pix_%(car_type)s_driver::report_parser::ReportParser"
  EXECUTABLE ${PROJECT_NAME}_report_parser_node
)

# install
ament_auto_package(
  INSTALL_TO_SHARE
  launch
  # config
)