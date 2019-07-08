#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Float32.h"

#include <ecal/ecal.h>
#include <ecal/msg/protobuf/publisher.h>

#include <iostream>
#include <chrono>
#include <thread>

#include "ecal_bridge/protobuf/encoder.pb.h"

float passthrough = 0;

// Pass recieved ROS message to main eCAL loop
void velCallback(const std_msgs::Float32::ConstPtr& vel)
{
  //ROS_INFO("Velocity: %f", vel->data);
  passthrough = vel-> data;
}

int main(int argc, char **argv)
{
  // Initialize eCAL process and publisher
  eCAL::Initialize(argc, argv, "encoder publisher");
  eCAL::Process::SetState(proc_sev_healthy, proc_sev_level1, "I drive good !");
  eCAL::protobuf::CPublisher<pb::Encoder::Encoder> pub("encoder");
  pub.SetRefFrequency(1.0, 3.0);
  pb::Encoder::Encoder encoder;
  
  // Initialize ROS node and subscriber
  ros::init(argc, argv, "listener");
  ros::NodeHandle n;
  ros::Subscriber vel_sub = n.subscribe<std_msgs::Float32>("velocity", 1000, velCallback);
  
  // Setup loop to publish eCAL messages 
  int count = 0;
  ros::Rate loop_rate(10);
  while(ros::ok())
  {
	encoder.set_vel(passthrough);
	pub.SetID(++count);
	pub.Send(encoder);

    //std::cout << "car velocity : " << encoder.vel() << std::endl;
	
	ros::spinOnce();
	loop_rate.sleep();
  }

  eCAL::Finalize();

  return(0);
}
