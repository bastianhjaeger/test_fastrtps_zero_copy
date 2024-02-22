cmake_minimum_required(VERSION 3.8)
project(test_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic -O3)
endif()

find_package(ament_cmake REQUIRED)
find_package(ament_cmake_ros REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)

########################################
#   Configure target
########################################

set(node_plugins "")

add_library(producer SHARED src/producer.cpp)
target_include_directories(producer PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
target_compile_features(producer PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17
ament_target_dependencies(producer
  rclcpp
  rclcpp_components
  std_msgs
)
rclcpp_components_register_nodes(producer "TestPkg::Producer")
set(node_plugins "${node_plugins}TestPkg::Producer;$<TARGET_FILE:producer>\n")

add_library(consumer SHARED src/consumer.cpp)
target_include_directories(consumer PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
target_compile_features(consumer PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17
ament_target_dependencies(consumer
  rclcpp
  rclcpp_components
  std_msgs
)
rclcpp_components_register_nodes(consumer "TestPkg::Consumer")
set(node_plugins "${node_plugins}TestPkg::Consumer;$<TARGET_FILE:consumer>\n")

########################################
#   Install
########################################

install(DIRECTORY launch config
  DESTINATION share/${PROJECT_NAME}
)
install(
  TARGETS producer consumer
  #ARCHIVE DESTINATION lib
  #LIBRARY DESTINATION lib
  #RUNTIME DESTINATION bin
	DESTINATION lib
)

file(GENERATE
  OUTPUT
  "${CMAKE_CURRENT_BINARY_DIR}/test_ament_index/$<CONFIG>/share/ament_index/resource_index/node_plugin/${PROJECT_NAME}"
  CONTENT "${node_plugins}")

ament_package()
