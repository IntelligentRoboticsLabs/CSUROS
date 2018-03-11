cmake_minimum_required(VERSION 2.8.3)
project(csuro_rqt)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  roscpp
  roslint
  rqt_gui
  rqt_gui_cpp
  std_msgs
)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Xml REQUIRED)

roslint_cpp()


catkin_package(
   LIBRARIES csuro_rqt
   CATKIN_DEPENDS roscpp rqt_gui_cpp std_msgs geometry_msgs
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations


set (twist_cmd_SRCS
  src/csuro_rqt/TwistCmd.cpp
)

set(twist_cmd_HDRS
  include/csuro_rqt/TwistCmd.h
)

set(twist_cmd_UIS
  src/csuro_rqt/TwistCmd.ui
)

qt5_wrap_cpp(twist_cmd_MOCS ${twist_cmd_HDRS})
qt5_wrap_ui(twist_cmd_UIS_H ${twist_cmd_UIS})

include_directories(
  include
  ${CMAKE_CURRENT_BINARY_DIR}/..
  ${catkin_INCLUDE_DIRS}
)

add_library(twist_cmd
    ${twist_cmd_SRCS}
    ${twist_cmd_MOCS}
    ${twist_cmd_UIS_H}
    )

target_link_libraries(twist_cmd
      ${catkin_LIBRARIES}
      Qt5::Widgets
      Qt5::Xml
    )


#############
## Install ##
#############

# all install targets should use catkin DESTINATION variables
# See http://ros.org/doc/api/catkin/html/adv_user_guide/variables.html


install(PROGRAMS scripts/twist_cmd
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
