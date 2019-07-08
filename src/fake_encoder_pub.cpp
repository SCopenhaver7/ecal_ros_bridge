#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Float32.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "face_encoder");

  ros::NodeHandle n;

  ros::Publisher encoder_pub = n.advertise<std_msgs::Float32>("velocity", 1000);

  ros::Rate loop_rate(10);


  int count = 0;
  while (ros::ok())
  {

    std_msgs::String msg;

    std_msgs::Float32 vel;
    vel.data = count;

    encoder_pub.publish(vel);

    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }


  return 0;
}
