cmake_minimum_required(VERSION 2.8.3)
set (CMAKE_CXX_STANDARD 11)
project(ecal_bridge)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  message_runtime
  message_generation
  sensor_msgs
  grpc
)
find_package(Protobuf 3.5.1 REQUIRED)
find_package(eCAL REQUIRED)

## Generate messages in the 'msg' folder
# add_message_files(
#   FILES
#   Message1.msg
#   Message2.msg
# )

## Generate added messages and services with any dependencies listed here
# generate_messages(
#   DEPENDENCIES
#   std_msgs
# )


catkin_package(
  CATKIN_DEPENDS roscpp rospy std_msgs grpc
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
  ${catkin_INCLUDE_DIRS}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
)


 #add_library(${PROJECT_NAME}
 #  src/${PROJECT_NAME}/ecal_bridge.cpp
 #)

# add_dependencies(${PROJECT_NAME} ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

generate_proto(msgName_proto protobuf/msgName.proto)

add_executable(ros_to_ecal src/ros_to_ecal.cpp)

target_link_libraries(ros_to_ecal
   ${catkin_LIBRARIES}
   protobuf 
   eCAL::core 
   ${PROTOBUF_LIBRARY}
   msgName_proto
 )
 
 add_executable(ecal_to_ros src/ecal_to_ros.cpp)
 
 target_link_libraries(ecal_to_ros
   ${catkin_LIBRARIES}
   protobuf 
   eCAL::core 
   ${PROTOBUF_LIBRARY}
   msgName_proto
 )
