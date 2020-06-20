#include<ros.h>
#include<sensor_msgs/Range.h>
int trigger = 9;
int echo = 10;
float dist;
float duration;
char frame_id[] = "ultrasonic_r";
ros::NodeHandle nh;
sensor_msgs::Range range;
ros::Publisher ultrasonic_pub("ultrasound_r",&range);

void setup() {
 pinMode(trigger,OUTPUT);
 pinMode(echo,INPUT);
 nh.initNode();
 nh.advertise(ultrasonic_pub);

}

void loop() {
  get_ultrasonic_data();
  ultrasonic_pub.publish(&range);
  delay(10);
  nh.spinOnce();
  delay(10);

}

void get_ultrasonic_data()
{
  digitalWrite(trigger,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger,LOW);
  duration = pulseIn(echo,HIGH);
  dist = (duration/5800.0);
  if (dist >= 0.5)
  {
    dist = 0.5;
    
   }
  if(dist <= 0.04)
  {
   dist = 0.04;  
    
  }
  range.range = dist;
  range.max_range = 0.5;
  range.min_range = 0.04;
  range.field_of_view = 0.0009;
  range.header.frame_id = frame_id;
  
  
  }
