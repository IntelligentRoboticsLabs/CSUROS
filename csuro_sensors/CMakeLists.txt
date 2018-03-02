cmake_minimum_required(VERSION 2.8.3)
project(csuro_sensors)


find_package(catkin REQUIRED COMPONENTS
  csuro_tools
  geometry_msgs
  pcl_ros
  roscpp
  rospy
  tf
  pcl_conversions
)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES ${PROJECT_NAME}
  CATKIN_DEPENDS ${PACKAGE_DEPENDENCIES}
  DEPENDS PCL
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

set(LINK_LIBS
  ${catkin_LIBRARIES}
)

add_executable(nodo_rgbd_filter 
	src/nodo_rgbd_filter.cpp
)
add_executable(nodo_rgbd_tf 
	src/nodo_rgbd_tf.cpp
)

target_link_libraries(nodo_rgbd_filter ${catkin_LIBRARIES})
target_link_libraries(nodo_rgbd_tf ${catkin_LIBRARIES})