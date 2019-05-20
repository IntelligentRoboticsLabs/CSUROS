cmake_minimum_required(VERSION 2.8.3)
project(csuro_tools)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  sensor_msgs
  std_msgs
  tf
  cv_bridge
  image_transport
  pcl_conversions
  pcl_ros
)

find_package(OpenCV)
include_directories(${OpenCV_INCLUDE_DIRS})


include_directories(
	${PCL_INCLUDE_DIRS}
)

link_directories(
	${PCL_LIBRARY_DIRS}
#	${Opencv_LIBRARY_DIRS}

)

add_definitions(${PCL_DEFINITIONS})

catkin_package(
	CATKIN_DEPENDS roscpp std_msgs
	INCLUDE_DIRS include
	LIBRARIES csurotools
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_library(csurotools
	src/Scan.cpp
	src/PIDController.cpp
)

add_executable(nodo_hsv_tuner_2d
	src/nodo_hsv_tuner_2d.cpp
)
add_executable(nodo_markers
	src/nodo_markers.cpp
)
add_executable(nodo_test_scan
  src/Scan.cpp
  src/nodo_test_scan.cpp
)
add_executable(image_publisher
	src/image_publisher_from_disk.cpp
)

target_link_libraries(csurotools ${catkin_LIBRARIES})
target_link_libraries(nodo_hsv_tuner_2d ${catkin_LIBRARIES} ${OpenCV_LIBRARIES} )
target_link_libraries(nodo_markers ${catkin_LIBRARIES})
target_link_libraries(nodo_test_scan ${catkin_LIBRARIES})
target_link_libraries(image_publisher ${catkin_LIBRARIES} ${OpenCV_LIBRARIES} )
