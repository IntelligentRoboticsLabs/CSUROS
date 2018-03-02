cmake_minimum_required(VERSION 2.8.3)
project(csuro_tf)


find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  roscpp
  rospy
  tf
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES csuro_tf
#  CATKIN_DEPENDS geometry_msgs roscpp rospy tf
#  DEPENDS system_lib
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

set(LINK_LIBS
  ${catkin_LIBRARIES}
)

add_executable(nodo_tf_pub 
	src/nodo_tf_pub.cpp
)
add_executable(nodo_tf_sub 
	src/nodo_tf_sub.cpp
)

target_link_libraries(nodo_tf_pub ${catkin_LIBRARIES})
target_link_libraries(nodo_tf_sub ${catkin_LIBRARIES})