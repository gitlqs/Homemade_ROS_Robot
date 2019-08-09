#include <Arduino.h>
#include <ros.h>
#include <geometry_msgs/Twist.h>

// define pin number
#define rightForward 11
#define rightBackward 10
#define leftForward 9
#define leftBackward 6

#define distanceBetweenTwoWheels 0.2459 // in meter

float x;

ros::NodeHandle nh;

void velCallback(const geometry_msgs::Twist &vel){
  // send velocity to motor
  double linearX = vel.linear.x;
  double angularZ = vel.angular.z;

  double linVelRight = linearX + angularZ * (distanceBetweenTwoWheels/2);
  double linVelLeft = linearX - angularZ * (distanceBetweenTwoWheels/2);

  double analogValue;

// calculate the analog write value using the calibration equation
// if the analog write value is larger than 255, make it 255
// if it is less than 0, make it 0
// refer to the wheelSpeedCalibration.xlsx for the calibration equation
  if (linVelRight>0){
    analogValue = 1585.0984787483 * linVelRight - 56.6542464493;
    if (analogValue>255){
      analogValue = 255;
    }
    else if (analogValue<0){
      analogValue = 0;
    }
    analogWrite(rightBackward, 0);
    analogWrite(rightForward, analogValue);
  }
  else if (linVelRight == 0){
    analogWrite(rightBackward, 0);
    analogWrite(rightForward, 0);
  }
  else{
    analogValue = 1585.0984787483 * (-linVelRight) - 56.6542464493;
    if (analogValue>255){
      analogValue = 255;
    }
    else if (analogValue<0){
      analogValue = 0;
    }
    analogWrite(rightBackward, analogValue);
    analogWrite(rightForward, 0);
  }

  if (linVelLeft>0){
    analogValue = 1585.0984787483 * linVelLeft - 56.6542464493;
    if (analogValue>255){
      analogValue = 255;
    }
    else if (analogValue<0){
      analogValue = 0;
    }
    analogWrite(leftBackward, 0);
    analogWrite(leftForward, analogValue);
  }
  else if (linVelLeft == 0){
    analogWrite(leftBackward, 0);
    analogWrite(leftForward, 0);
  }
  else{
    analogValue = 1585.0984787483 * (-linVelLeft) - 56.6542464493;
    if (analogValue>255){
      analogValue = 255;
    }
    else if (analogValue<0){
      analogValue = 0;
    }
    analogWrite(leftBackward, analogValue);
    analogWrite(leftForward, 0);
  }

// TODO: Read encoder data
// TODO: Publish data on /odom topic

}

ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel", velCallback);

void setup(){
  pinMode(rightForward, OUTPUT);
  pinMode(rightBackward, OUTPUT);
  pinMode(leftForward, OUTPUT);
  pinMode(leftBackward, OUTPUT);

  nh.initNode();
  nh.subscribe(sub);
}

void loop(){
  nh.spinOnce();
  delay(10);
}
