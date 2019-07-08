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

generate_proto(encoder_proto protobuf/encoder.proto)

add_executable(bridge_node src/bridge_node.cpp)

target_link_libraries(bridge_node
   ${catkin_LIBRARIES}
   protobuf 
   eCAL::core 
   ${PROTOBUF_LIBRARY}
   encoder_proto
 )
 
 add_executable(fake_encoder src/fake_encoder_pub.cpp)
 
 target_link_libraries(fake_encoder
   ${catkin_LIBRARIES}
 )
 
 add_executable(ecal_to_ros src/ecal_to_ros.cpp)
 
 target_link_libraries(ecal_to_ros
   ${catkin_LIBRARIES}
   protobuf 
   eCAL::core 
   ${PROTOBUF_LIBRARY}
   encoder_proto
 )
