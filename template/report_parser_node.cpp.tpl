#include <pix_%(car_type)s_driver/report_parser.hpp>
#include <rclcpp/rclcpp.hpp>
#include <memory>

int main(int argc, char ** argv)
{ 
  rclcpp::init(argc, argv);
  auto node = std::make_shared<pix_%(car_type)s_driver::report_parser::ReportParser>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}