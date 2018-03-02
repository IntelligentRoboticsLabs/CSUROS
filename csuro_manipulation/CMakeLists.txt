cmake_minimum_required(VERSION 2.8.3)
project(csuro_manipulation)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  actionlib
  arbotix_msgs
  cmake_modules
  control_msgs
  moveit_core
  moveit_ros_perception
  moveit_ros_planning_interface
  phantomx_lib
  pluginlib
  roscpp
  rospy
  sensor_msgs
  tf
  tf_conversions
  trajectory_msgs
)

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

find_package(Boost REQUIRED COMPONENTS system)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES csuro_comms_cpp
#  CATKIN_DEPENDS roscpp actionlib_msgs
#  DEPENDS system_lib
)

include_directories(
  ${catkin_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
)

add_executable(test_manipulation_node src/test_manipulation_node.cpp)
add_executable(pick_manipulation_node src/pick_manipulation_node.cpp)
add_executable(gripper_manipulation_node src/gripper_manipulation_node.cpp)

target_link_libraries(test_manipulation_node ${catkin_LIBRARIES})
target_link_libraries(pick_manipulation_node ${catkin_LIBRARIES})
target_link_libraries(gripper_manipulation_node ${catkin_LIBRARIES})
