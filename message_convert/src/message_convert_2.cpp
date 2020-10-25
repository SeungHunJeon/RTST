#include <ros/ros.h>
#include <stdio.h>
#include <std_msgs/Int16.h>
#include "std_msgs/Float64.h"
#include <darknet_ros_msgs/BoundingBox.h>
#include <darknet_ros_msgs/BoundingBoxes.h>
#include <darknet_ros_msgs/CheckForObjectsAction.h>
#include <darknet_ros_msgs/ObjectCount.h>
#include <std_msgs/Header.h>
#include <chrono>
#include <cmath>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

// darknet_ros_msgs::BoundingBox bounding_box; 
// std_msgs::int ID;
std_msgs::Float64 prob;
void msg_cb(darknet_ros_msgs::BoundingBox msg)
{
  prob.data = msg.probability;
  
//   pub.publish(bounding_box);
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "message_convert_2");
  ros::NodeHandle nh;
  ros::Rate loop_rate(30);
  ros::Publisher pub = nh.advertise<std_msgs::Float64>("/object_id", 1);
  ros::Subscriber sub = nh.subscribe("/non_array", 1, msg_cb);

  
  while(ros::ok()){
  	pub.publish(prob);
  	ros::spinOnce();
  	
  	loop_rate.sleep();
  	
  }
  
  return 0;
}