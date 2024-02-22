import launch
from launch_ros.actions import ComposableNodeContainer
from launch_ros.descriptions import ComposableNode

def generate_launch_description():
    container = ComposableNodeContainer(
            name='my_container1',
            namespace='',
            package='rclcpp_components',
            executable='component_container_mt',
            composable_node_descriptions=[
                ComposableNode(
                    package='test_pkg',
                    plugin='TestPkg::Producer',
                    name='produ',
                    extra_arguments=[
                        {'use_intra_process_comms' : False}
                    ]
                )
            ],
            output='screen',
    );

    container2 = ComposableNodeContainer(
            name='my_container2',
            namespace='',
            package='rclcpp_components',
            executable='component_container_mt',
            composable_node_descriptions=[
                ComposableNode(
                    package='test_pkg',
                    plugin='TestPkg::Consumer',
                    name='consu',
                    extra_arguments=[
                        {'use_intra_process_comms' : False}
                    ]
                )
            ],
            output='screen',
    );

    return launch.LaunchDescription(
        [
            container,
            container2
        ]
    )