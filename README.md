# preparation

```
cd <your-colcon-ws>
export ROS_DISABLE_LOANED_MESSAGES=0
export FASTRTPS_DEFAULT_PROFILES_FILE=$(pwd)/src/test_pkg/CustomFastRTPSProfile.xml
export RMW_FASTRTPS_USE_QOS_FROM_XML=1

```

# zero copy working for intra-process communication

```
$ ros2 launch test_pkg launch.py
[INFO] [launch]: All log files can be found below /home/me/.ros/log/2024-02-22-16-50-59-867980-yoga-9i-64230
[INFO] [launch]: Default logging verbosity is set to INFO
[INFO] [component_container_mt-1]: process started with pid [64251]
[component_container_mt-1] [INFO] [1708617060.237477556] [my_container]: Load Library: /home/me/dev/colcon-ws/install/lib/libproducer.so
[component_container_mt-1] [INFO] [1708617060.237965011] [my_container]: Found class: rclcpp_components::NodeFactoryTemplate<TestPkg::Producer>
[component_container_mt-1] [INFO] [1708617060.238004729] [my_container]: Instantiate class: rclcpp_components::NodeFactoryTemplate<TestPkg::Producer>
[INFO] [launch_ros.actions.load_composable_nodes]: Loaded node '/produ' in container '/my_container'
[component_container_mt-1] [INFO] [1708617060.241580978] [my_container]: Load Library: /home/me/dev/colcon-ws/install/lib/libconsumer.so
[component_container_mt-1] [INFO] [1708617060.242160358] [my_container]: Found class: rclcpp_components::NodeFactoryTemplate<TestPkg::Consumer>
[component_container_mt-1] [INFO] [1708617060.242172644] [my_container]: Instantiate class: rclcpp_components::NodeFactoryTemplate<TestPkg::Consumer>
[INFO] [launch_ros.actions.load_composable_nodes]: Loaded node '/consu' in container '/my_container'
[component_container_mt-1] [INFO] [1708617061.240519612] [produ]: Published message with value: 0, and address: 0x7F4A24000B70
[component_container_mt-1] [INFO] [1708617061.240681067] [consu]:  Received message with value: 0, and address: 0x7F4A24000B70
[component_container_mt-1] [INFO] [1708617062.240599445] [produ]: Published message with value: 1, and address: 0x7F4A4C001580
[component_container_mt-1] [INFO] [1708617062.240714209] [consu]:  Received message with value: 1, and address: 0x7F4A4C001580
[component_container_mt-1] [INFO] [1708617063.240608108] [produ]: Published message with value: 2, and address: 0x7F4A4C001580
[component_container_mt-1] [INFO] [1708617063.240713868] [consu]:  Received message with value: 2, and address: 0x7F4A4C001580
^C[WARNING] [launch]: user interrupted with ctrl-c (SIGINT)
[component_container_mt-1] [INFO] [1708617063.590941859] [rclcpp]: signal_handler(signum=2)
[INFO] [component_container_mt-1]: process has finished cleanly [pid 64251]
```

# zero copy NOT working for inter-process communication

```
$ ros2 launch test_pkg launch2.py
[INFO] [launch]: All log files can be found below /home/me/.ros/log/2024-02-22-16-50-48-145847-yoga-9i-64101
[INFO] [launch]: Default logging verbosity is set to INFO
[INFO] [component_container_mt-1]: process started with pid [64114]
[INFO] [component_container_mt-2]: process started with pid [64116]
[component_container_mt-1] [INFO] [1708617048.531853519] [my_container1]: Load Library: /home/me/dev/colcon-ws/install/lib/libproducer.so
[component_container_mt-1] [INFO] [1708617048.532302816] [my_container1]: Found class: rclcpp_components::NodeFactoryTemplate<TestPkg::Producer>
[component_container_mt-1] [INFO] [1708617048.532349362] [my_container1]: Instantiate class: rclcpp_components::NodeFactoryTemplate<TestPkg::Producer>
[component_container_mt-2] [INFO] [1708617048.532605142] [my_container2]: Load Library: /home/me/dev/colcon-ws/install/lib/libconsumer.so
[component_container_mt-2] [INFO] [1708617048.533682425] [my_container2]: Found class: rclcpp_components::NodeFactoryTemplate<TestPkg::Consumer>
[component_container_mt-2] [INFO] [1708617048.533696027] [my_container2]: Instantiate class: rclcpp_components::NodeFactoryTemplate<TestPkg::Consumer>
[INFO] [launch_ros.actions.load_composable_nodes]: Loaded node '/produ' in container '/my_container1'
[INFO] [launch_ros.actions.load_composable_nodes]: Loaded node '/consu' in container '/my_container2'
[component_container_mt-1] [INFO] [1708617049.536348344] [produ]: Publ loan message with value: 0, and address: 0x7FACB4000BA0
[component_container_mt-2] [WARN] [1708617049.536578308] [consu]: Loaned messages are only safe with const ref subscription callbacks. If you are using any other kind of subscriptions, set the ROS_DISABLE_LOANED_MESSAGES environment variable to 1 (the default).
[component_container_mt-2] [INFO] [1708617049.536671898] [consu]:  Received message with value: 0, and address: 0x7F9C8C001040
[component_container_mt-1] [INFO] [1708617050.536092874] [produ]: Publ loan message with value: 1, and address: 0x7FACD40025D0
[component_container_mt-2] [INFO] [1708617050.536317914] [consu]:  Received message with value: 1, and address: 0x7F9C84000F10
[component_container_mt-1] [INFO] [1708617051.536115314] [produ]: Publ loan message with value: 2, and address: 0x7FACC4001140
[component_container_mt-2] [INFO] [1708617051.536325942] [consu]:  Received message with value: 2, and address: 0x7F9CCC002110
```