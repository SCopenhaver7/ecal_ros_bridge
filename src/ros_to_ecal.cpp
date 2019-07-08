#include "ros/ros.h"
#include "std_msgs/String.h"

#include <ecal/ecal.h>
#include <ecal/msg/protobuf/publisher.h>

#include <iostream>
#include <chrono>
#include <thread>

#include "ecal_bridge/protobuf/msgName.pb.h"

std::string passthrough = "";

// Pass recieved ROS message to main eCAL loop
void ROSCallback(const std_msgs::String::ConstPtr& str)
{
  passthrough = str->data.c_str();
}

int main(int argc, char **argv)
{
  // Initialize eCAL process and publisher
  eCAL::Initialize(argc, argv, "message publisher");
  eCAL::Process::SetState(proc_sev_healthy, proc_sev_level1, "I feel good !");
  eCAL::protobuf::CPublisher<pkgName::msgName> pub("testMsg_eCAL");
  pub.SetRefFrequency(1.0, 3.0);
  pkgName::msgName msg;
  
  // Initialize ROS node and subscriber
  ros::init(argc, argv, "listener");
  ros::NodeHandle n;
  ros::Subscriber msgName_sub = n.subscribe<std_msgs::String>("testMsg_ROS", 1000, ROSCallback);
  
  // Setup loop to publish eCAL messages 
  int count = 0;
  ros::Rate loop_rate(10);
  while(ros::ok())
  {
	msg.set_data(passthrough);
	pub.Send(msg);
	
	ros::spinOnce();
	loop_rate.sleep();
  }

  eCAL::Finalize();

  return(0);
}
