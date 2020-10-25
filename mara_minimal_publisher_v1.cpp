#include <iostream>
#include "rclcpp/rclcpp.hpp"
#include "hrim_actuator_rotaryservo_msgs/msg/goal_rotary_servo.hpp"
#include "hrim_actuator_rotaryservo_msgs/msg/state_rotary_servo.hpp"
#include "std_msgs/msg/int16.hpp"


int object_id=0;
int switch_value = 0;
float object_position=0;
float position_axis_1 = 0;
float position_axis_2 = 0;
float position_angle = 0;

void msgCallback(const std_msgs::msg::Int16::SharedPtr msg)
{
  std::cout<<"Bouding Boxes (ID):" << msg->data <<std::endl;
  object_id = msg->data;
}


void minimal_callback1(const hrim_actuator_rotaryservo_msgs::msg::StateRotaryServo::UniquePtr msg)
{
  //std::cout << "Position1: " << msg->position << std::endl;
  position_axis_1 = msg->position;
}

void minimal_callback2(const hrim_actuator_rotaryservo_msgs::msg::StateRotaryServo::UniquePtr msg)
{
  //std::cout << "Position2: " << msg->position << std::endl;
  position_axis_2 = msg->position;
}

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);

  // Create Node with name "mara_minimal_publisher"
  auto node = rclcpp::Node::make_shared("mara_minimal_publisher");

  // Create a publisher on topic "/hrim_actuation_servomotor_000000000001/goal_axis2"
  auto pub1 = node->create_publisher<hrim_actuator_rotaryservo_msgs::msg::GoalRotaryServo>("/hrim_actuator_rotaryservo_000000000001/goal_axis1", rclcpp::SensorDataQoS());

  auto pub2 = node->create_publisher<hrim_actuator_rotaryservo_msgs::msg::GoalRotaryServo>("/hrim_actuator_rotaryservo_000000000001/goal_axis2", rclcpp::SensorDataQoS());

  // Publishing rate of 1 Hzposition_axis_1
  rclcpp::WallRate loop_rate(1);

  // Create message with the same type as the topic, <hrim_actuator_rotaryservo_msgs::msg::GoalRotaryServo>.
  auto msg_axis_1 = std::make_shared<hrim_actuator_rotaryservo_msgs::msg::GoalRotaryServo>();
  auto msg_axis_2 = std::make_shared<hrim_actuator_rotaryservo_msgs::msg::GoalRotaryServo>();
  // Desired position in degrees

  
  auto sub = node->create_subscription<std_msgs::msg::Int16>(
    "/object_id",
    rclcpp::SensorDataQoS(), // QoS profile for reading (joint) sensors
    msgCallback);

  auto sub1 = node->create_subscription<hrim_actuator_rotaryservo_msgs::msg::StateRotaryServo>(
    "/hrim_actuator_rotaryservo_000000000001/state_axis1",
    rclcpp::SensorDataQoS(), // QoS profile for reading (joint) sensors
    minimal_callback1);

  auto sub2 = node->create_subscription<hrim_actuator_rotaryservo_msgs::msg::StateRotaryServo>(
    "/hrim_actuator_rotaryservo_000000000001/state_axis2",
    rclcpp::SensorDataQoS(), // QoS profile for reading (joint) sensors
    minimal_callback2);

  // Loop for axis 2 90 degree rotation ( x - axis rotation )

  int i = 1; // Loop counter
  while (rclcpp::ok()) {
    // Fill message content
    
    msg_axis_1->position = 90 * 3.1416/180.0; // Position to rads
    msg_axis_1->velocity = 0.4; // Velocity in rads/s
    msg_axis_1->control_type = 4; // Position and velocity control

    printf("axis1 value setting fin.\n");
    if(switch_value == 0)
    {
      pub1->publish(*msg_axis_1);
      if(std::abs(position_axis_1 - msg_axis_1->position) < 0.01)
      {
        
        switch_value = 1;
        printf("switch\n");
      }

    }
    if(switch_value == 1)
    printf("axis1 move fin.\n");
    rclcpp::spin_some(node);
    if(switch_value == 1){
    if(object_id == 15) //dog
    {
      object_position = 270;
      switch_value = 2;
      msg_axis_2->position = object_position * 3.1416/180.0; // Position to rads
      msg_axis_2->velocity = 0.4; // Velocity in rads/s
      msg_axis_2->control_type = 4; // Position and velocity control

    }

    else if(object_id == 14) //bird
    {
      object_position = 90;
      switch_value = 2;
      msg_axis_2->position = object_position * 3.1416/180.0; // Position to rads
      msg_axis_2->velocity = 0.4; // Velocity in rads/s
      msg_axis_2->control_type = 4; // Position and velocity control
    }

    else if(object_id == 62) //TV monitor
    {
      object_position = 180;
      switch_value = 2;
      msg_axis_2->position = object_position * 3.1416/180.0; // Position to rads
      msg_axis_2->velocity = 0.4; // Velocity in rads/s
      msg_axis_2->control_type = 4; // Position and velocity control
    }

    else
    {
      switch_value=1;
    }
    }
    if(switch_value == 2){
      printf("axis2 value setting fin.");
      pub2->publish(*msg_axis_2);
      if ((std::abs(position_axis_2 - msg_axis_2->position) < 0.01))
      {
        printf("axis2 move fin.");
        switch_value = 1;
      }
    }

    // Publish message!
    // Spin not really needed here since we don't have callbacks


    // Sleep to mantain the 1 Hz publishing rate
    loop_rate.sleep();

    // Log
    RCLCPP_INFO(node->get_logger(), "Iteration1 number %d", i);
    i++;


  }
// Loop for z axis rotation (specific position)


 //  i = 1;
 //  printf("END MOTOR1\n");

 // //  if ( state == 0 )
 // //  {
	// // position_angle = -45;
 // //  }

 // //  else if( state == 1 )
 // //  {
 // //  	position_angle = 0;
 // //  }

 // //  else if (state == 2)
 // //  {
 // //  	position_angle = 45;
 // //  }

 //    if(object_id == 63)
 //  {
 //    printf("ID IS 63\n");
 //    object_position=90;
 //  }
 //  else if(object_id == 41)
 //  {
 //    object_position=180;
 //    printf("ID IS 41\n");
 //  }
 //  else
 //  {
 //    printf("NOTHING\n");
 //  }


  

  // while (rclcpp::ok()) {
  //   // Fill message content
  //   printf("second while\n");
  //   msg_axis_2->position = object_position * 3.1416/180.0; // Position to rads
  //   msg_axis_2->velocity = 0.4; // Velocity in rads/s
  //   msg_axis_2->control_type = 4; // Position and velocity control

  //   if (std::abs(position_axis_2 - msg_axis_2->position) < 0.01){
  //     break;
  //   }
  //   // Publish message!
  //   pub2->publish(*msg_axis_2);

  //   // Spin not really needed here since we don't have callbacks
  //   rclcpp::spin_some(node);

  //   // Sleep to mantain the 1 Hz publishing rate
  //   loop_rate.sleep();

  //   // Log
  //   RCLCPP_INFO(node->get_logger(), "Iteration number %d", i);
  //   i++;
  // }
  

  rclcpp::spin(node);
  rclcpp::shutdown();

  return 0;
}
