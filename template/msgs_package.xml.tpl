<?xml version="1.0"?>
<?xml-model href="http://download.ros.org/schema/package_format3.xsd" schematypens="http://www.w3.org/2001/XMLSchema"?>
<package format="3">
  <name>pix_%(car_type)s_driver_msgs</name>
  <version>0.9.0</version>
  <description>The pix_%(car_type)s_driver_msg package</description>
  <maintainer email="pixmoving@pixmoving.net">pixmoving</maintainer>

  <license>Apache License 2.0</license>

  <buildtool_depend>ament_cmake_auto</buildtool_depend>
  <buildtool_depend>rosidl_default_generators</buildtool_depend>

  <depend>builtin_interfaces</depend>
  <depend>std_msgs</depend>

  <exec_depend>rosidl_default_runtime</exec_depend>

  <test_depend>ament_lint_auto</test_depend>
  <test_depend>ament_lint_common</test_depend>

  <member_of_group>rosidl_interface_packages</member_of_group>

  <export>
    <build_type>ament_cmake</build_type>
  </export>
</package>
