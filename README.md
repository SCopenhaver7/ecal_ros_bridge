# ecal_ros_bridge
This package is a template for creating a bridge between ROS and eCAL
Tested on ROS kinetic and eCAL 5.3.2

## Set Up
- Pull this package inside of a ROS catkin workspace
- Pull the package `catkin_grpc` from https://github.com/CogRob/catkin_grpc inside of the same workspace
- Build the workspace

## Outline

### `ros_to_ecal`
In this node, add subscribers to any ROS messages that you wish to pass to eCAL and add eCAL publishers for each ROS message. All messages are published to eCAL inside the main method, with global variables used to pass data from the ROS callbacks to the main method.

### `ecal_to_ros`
In this node, add subscribers to any eCAL messages that you wish to pass to ROS and add ROS publishers for each eCAL message. All ROS messages are published inside of their respective eCAL callbacks, as ROS publishers can be declared globally.

### Protobuf Messages
To add a new protobuf message, place your `.proto` file in the `protobuf` folder, then add the line `generate_proto(<your_message_name>_proto protobuf/<your_message_name>.proto)` to the CMakeLists
