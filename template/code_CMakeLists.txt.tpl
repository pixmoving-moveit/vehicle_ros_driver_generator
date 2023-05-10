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

ament_auto_add_executable(${PROJECT_NAME}_control_command_node
  %(command_cpp_list)s
  src/Byte.cc
  src/control_command.cpp
  src/control_command_node.cpp
)

ament_auto_add_executable(${PROJECT_NAME}_report_parser_node
  %(report_cpp_list)s
  src/Byte.cc
  src/report_parser.cpp
  src/report_parser_node.cpp
)

# install
ament_auto_package(
  INSTALL_TO_SHARE
  launch
  # config
)