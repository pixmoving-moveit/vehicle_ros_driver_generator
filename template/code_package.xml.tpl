<?xml version="1.0"?>
<?xml-model href="http://download.ros.org/schema/package_format3.xsd" schematypens="http://www.w3.org/2001/XMLSchema"?>
<package format="3">
  <name>pix_%(car_type)s_driver</name>
  <version>0.9.0</version>
  <description>The pix_%(car_type)s_driver package</description>
  <maintainer email="pixmoving@pixmoving.net">pixmoving</maintainer>
  <license>Apache License 2.0</license>

  <depend>can_msgs</depend>
  <depend>pix_%(car_type)s_driver_msgs</depend>
  <depend>rclcpp</depend>
  <depend>std_msgs</depend>

  <test_depend>ament_lint_auto</test_depend>
  <test_depend>autoware_lint_common</test_depend>

  <export>
    <build_type>ament_cmake</build_type>
  </export>
</package>
