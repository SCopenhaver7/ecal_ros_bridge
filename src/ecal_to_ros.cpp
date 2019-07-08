#include "ros/ros.h"
#include "std_msgs/String.h"

#include <ecal/ecal.h>
#include <ecal/msg/protobuf/subscriber.h>

#include <iostream>
#include <chrono>
#include <thread>

#include "ecal_bridge/protobuf/msgName.pb.h"

// ROS publisher is declared globally so it can be used in eCal callback
ros::Publisher msgName_pub2;

// Publish ROS msg when eCAL message is recieved
void ecalCallback(const char* topic_name_, const pkgName::msgName& msg_, const long long time_, const long long clock_, const long long id_)
{
  std_msgs::String str;
  str.data = msg_.data();
  msgName_pub2.publish(str);
}

int main(int argc, char **argv)
{
  // Initialize eCAL process and subscriber
  eCAL::Initialize(argc, argv, "message subscriber");
  eCAL::Process::SetState(proc_sev_healthy, proc_sev_level1, "I feel good !");
  std::this_thread::sleep_for(std::chrono::seconds(1));
  eCAL::protobuf::CSubscriber<pkgName::msgName> sub("testMsg_eCAL");
  sub.SetRefFrequency(1.0, 3.0);
  
  // Initialize ROS node and publisher
  ros::init(argc, argv, "ecal_to_ros");
  ros::NodeHandle n;
  msgName_pub2 = n.advertise<std_msgs::String>("testMsg_ROS", 1000);

  // add receive callback function (_1 = topic_name, _2 = msg, _3 = time, _4 = clock, _5 = id)
  auto callback = std::bind(ecalCallback, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5);
  sub.AddReceiveCallback(callback);
  
   ros::Rate loop_rate(10);
  
  // Loop until ROS is killed
  while(ros::ok())
  {
    ros::spinOnce();

    loop_rate.sleep();
  }

  eCAL::Finalize();
  
  return(0);
}

