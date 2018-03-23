cmake_minimum_required(VERSION 3.5)

project(csuro_intro_cpp)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rcutils)
find_package(rmw REQUIRED)
find_package(std_msgs REQUIRED)

add_executable(nodo_simple src/nodo_simple.cpp)
ament_target_dependencies(nodo_simple rclcpp rcutils std_msgs)
install(TARGETS nodo_simple DESTINATION lib/csuro_intro_cpp)

add_executable(nodo_iterativo src/nodo_iterativo.cpp)
ament_target_dependencies(nodo_iterativo rclcpp rcutils std_msgs)
install(TARGETS nodo_iterativo DESTINATION lib/csuro_intro_cpp)

add_executable(nodo_pub src/nodo_pub.cpp)
ament_target_dependencies(nodo_pub rclcpp rcutils std_msgs)
install(TARGETS nodo_pub DESTINATION lib/csuro_intro_cpp)

add_executable(nodo_pub_qos src/nodo_pub_qos.cpp)
ament_target_dependencies(nodo_pub_qos rclcpp rcutils std_msgs)
install(TARGETS nodo_pub_qos DESTINATION lib/csuro_intro_cpp)

add_executable(nodo_sub src/nodo_sub.cpp)
ament_target_dependencies(nodo_sub rclcpp rcutils std_msgs)
install(TARGETS nodo_sub DESTINATION lib/csuro_intro_cpp)

add_executable(nodo_sub_obj src/nodo_sub_obj.cpp)
ament_target_dependencies(nodo_sub_obj rclcpp rcutils std_msgs)
install(TARGETS nodo_sub_obj DESTINATION lib/csuro_intro_cpp)

ament_package()
