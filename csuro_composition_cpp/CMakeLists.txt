cmake_minimum_required(VERSION 3.5)

project(csuro_composition_cpp)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(class_loader REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rcutils)
find_package(rmw REQUIRED)
find_package(std_msgs REQUIRED)

include_directories(include)

add_library(subscriber_node src/subscriber.cpp)
ament_target_dependencies(subscriber_node rclcpp rcutils std_msgs class_loader)
install(TARGETS subscriber_node
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

add_library(publisher_node src/publisher.cpp)
ament_target_dependencies(publisher_node rclcpp rcutils std_msgs class_loader)
install(TARGETS publisher_node
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

add_executable(subscriber_proc src/subscriber_proc.cpp)
target_link_libraries(subscriber_proc subscriber_node)
ament_target_dependencies(subscriber_proc rclcpp class_loader)

add_executable(publisher_proc src/publisher_proc.cpp)
target_link_libraries(publisher_proc publisher_node)
ament_target_dependencies(publisher_proc rclcpp class_loader)

add_executable(composed src/composed.cpp)
target_link_libraries(composed publisher_node subscriber_node)
ament_target_dependencies(composed rclcpp class_loader)

install(TARGETS
  publisher_proc
  subscriber_proc
  composed
  DESTINATION lib/${PROJECT_NAME})


ament_package()
