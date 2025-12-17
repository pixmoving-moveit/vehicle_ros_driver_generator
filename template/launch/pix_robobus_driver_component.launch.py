# Copyright 2024 Pixmoving, Inc. All rights reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import os
from ament_index_python import get_package_share_directory

import launch
from launch.actions import DeclareLaunchArgument
from launch.actions import OpaqueFunction
from launch.actions import SetLaunchConfiguration
from launch.conditions import IfCondition
from launch.conditions import UnlessCondition
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import ComposableNodeContainer
from launch_ros.actions import LoadComposableNodes
from launch_ros.descriptions import ComposableNode
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
import yaml



def generate_launch_description():
    launch_arguments = []
    def add_launch_arg(name: str, default_value=None):
        launch_arguments.append(DeclareLaunchArgument(name, default_value=default_value))
    # 加载参数   ----------------------------------------------------------------------------------------
    add_launch_arg("control_container_name", "/control/control_container")
    add_launch_arg("base_frame_id", "base_link")
    add_launch_arg("loop_rate", "50.0")
    add_launch_arg("pix_interface_driver_period_ms", "50.0")
    
    def create_parameter_dict(*args):
        result = {}
        for x in args:
            result[x] = LaunchConfiguration(x)
        return result
    
    # 创建组件节点----------------------------------------------------------------------------------------
    control_command_component_node = ComposableNode(
        package="pix_robobus_driver",
        plugin="pix_robobus_driver::control_command::ControlCommand",
        name="pix_robobus_driver_control_command_node",
        namespace="",
        parameters=[
            create_parameter_dict(
                "base_frame_id",
                "loop_rate",
                "pix_interface_driver_period_ms"
            )
        ],
        remappings=[
                    ("output/can_tx", "/to_can_bus"),
                    ("input/engage", "/pix_robobus_driver/control_command/engage"),
                ],
    )
    

    report_parser_component_node = ComposableNode(
        package="pix_robobus_driver",
        plugin="pix_robobus_driver::report_parser::ReportParser",
        name="pix_robobus_driver_report_parser_node",
        namespace="",
        parameters=[
            create_parameter_dict(
                "base_frame_id",
                "loop_rate",
                "pix_interface_driver_period_ms"
            )
        ],
        remappings=[
                    ("input/can_rx", "/from_can_bus"),
                ],
    )
    
    
    # 加载组件节点-----------------------------------------------------------------------------------------
    pix_robobus_driver_loader = LoadComposableNodes(
        composable_node_descriptions=[
            control_command_component_node,
            report_parser_component_node
            ],
        target_container=LaunchConfiguration(
          'control_container_name'
          ),
    )

    return launch.LaunchDescription([
        *launch_arguments,
        pix_robobus_driver_loader,
        ]
    )