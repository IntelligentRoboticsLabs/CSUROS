cmake_minimum_required(VERSION 2.8.3)
project(csuro_comms_cpp)


find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  message_generation
  actionlib
  actionlib_msgs
)

find_package(Boost REQUIRED COMPONENTS system)

add_message_files(
   FILES
   Point.msg
 )

add_service_files(
   FILES
   Distance.srv
)

add_action_files(
   DIRECTORY action
   FILES Sequence.action
)

generate_messages(
   DEPENDENCIES
   std_msgs
   actionlib_msgs
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES csuro_comms_cpp
  CATKIN_DEPENDS roscpp std_msgs message_runtime actionlib_msgs
#  DEPENDS system_lib
)

include_directories(
  ${catkin_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
)

add_executable(nodo_point_sub src/nodo_point_sub.cpp)
add_executable(nodo_point_pub src/nodo_point_pub.cpp)
add_executable(nodo_distance_server src/nodo_distance_server.cpp)
add_executable(nodo_distance_client src/nodo_distance_client.cpp)
add_executable(nodo_sequence_server src/nodo_sequence_server.cpp)
add_executable(nodo_sequence_client src/nodo_sequence_client.cpp)

target_link_libraries(nodo_point_sub ${catkin_LIBRARIES})
target_link_libraries(nodo_point_pub ${catkin_LIBRARIES})
target_link_libraries(nodo_distance_client ${catkin_LIBRARIES})
target_link_libraries(nodo_distance_server ${catkin_LIBRARIES})
target_link_libraries(nodo_sequence_server ${catkin_LIBRARIES})
target_link_libraries(nodo_sequence_client ${catkin_LIBRARIES})

add_dependencies(nodo_point_sub csuro_comms_cpp_generate_messages_cpp)
add_dependencies(nodo_point_pub csuro_comms_cpp_generate_messages_cpp)
add_dependencies(nodo_distance_client csuro_comms_cpp_generate_messages_cpp)
add_dependencies(nodo_distance_server csuro_comms_cpp_generate_messages_cpp)

add_dependencies(nodo_sequence_server ${csuro_comms_cpp_EXPORTED_TARGETS})
add_dependencies(nodo_sequence_client ${csuro_comms_cpp_EXPORTED_TARGETS})

#############
## Install ##
#############

# all install targets should use catkin DESTINATION variables
# See http://ros.org/doc/api/catkin/html/adv_user_guide/variables.html

## Mark executable scripts (Python etc.) for installation
## in contrast to setup.py, you can choose the destination
# install(PROGRAMS
#   scripts/my_python_script
#   DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark executables and/or libraries for installation
# install(TARGETS csuro_comms_cpp csuro_comms_cpp_node
#   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark cpp header files for installation
# install(DIRECTORY include/${PROJECT_NAME}/
#   DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
#   FILES_MATCHING PATTERN "*.h"
#   PATTERN ".svn" EXCLUDE
# )

## Mark other files for installation (e.g. launch and bag files, etc.)
# install(FILES
#   # myfile1
#   # myfile2
#   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
# )

#############
## Testing ##
#############

## Add gtest based cpp test target and link libraries
# catkin_add_gtest(${PROJECT_NAME}-test test/test_csuro_comms_cpp.cpp)
# if(TARGET ${PROJECT_NAME}-test)
#   target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME})
# endif()

## Add folders to be run by python nosetests
# catkin_add_nosetests(test)
