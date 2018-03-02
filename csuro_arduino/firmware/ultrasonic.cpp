/*
 * rosserial Subscriber Example
 * Blinks an LED on callback
 */

#include <ros.h>
#include <std_msgs/Empty.h>
#include <std_msgs/Float32.h>
#include <kobuki_msgs/MotorPower.h>
#include <geometry_msgs/Twist.h>
#include <Arduino.h>

ros::NodeHandle nh;
const int EchoPin = 5;
const int TriggerPin = 6;
const int LedPin = 13;
const long minDistance = 15.0;

geometry_msgs::Twist velocity;
kobuki_msgs::MotorPower power;
std_msgs::Float32 distance;
ros::Publisher velocity_publisher("/mobile_base/commands/velocity", &velocity);
ros::Publisher motor_power_publisher("/motor_power", &power);
ros::Publisher distance_publisher("/distance", &distance);

void messageCb( const std_msgs::Empty& toggle_msg){
  digitalWrite(13, HIGH-digitalRead(13));   // blink the led
}
ros::Subscriber<std_msgs::Empty> sub("toggle_led", &messageCb );

void sensorAction(int TriggerPin, int EchoPin){
  long duration, distanceCm;
  float vel,velrot;
	digitalWrite(TriggerPin, LOW);  //para generar un pulso limpio ponemos a LOW 4us
	delayMicroseconds(4);
	digitalWrite(TriggerPin, HIGH);  //generamos Trigger (disparo) de 10us
	delayMicroseconds(10);
	digitalWrite(TriggerPin, LOW);

	duration = pulseIn(EchoPin, HIGH);  //medimos el tiempo entre pulsos, en microsegundos

	distanceCm = int(0.017*duration);   //convertimos a distancia, en cm
  distance.data = distanceCm;
  if(distanceCm < minDistance){
    vel = 0.5;
		velrot = 0.0;
		velocity.linear.x = vel;
		velocity.angular.z = velrot;
		velocity_publisher.publish(&velocity);		//le pasamos vel y lo publicamos
  }
  //distance_publisher.publish(&distance);
}

void setup()
{
  pinMode(LedPin, OUTPUT);
	pinMode(TriggerPin, OUTPUT);
	pinMode(EchoPin, INPUT);
  nh.initNode();
  nh.subscribe(sub);
  nh.advertise(motor_power_publisher);
  nh.advertise(velocity_publisher);
  nh.advertise(distance_publisher);
  power.state = kobuki_msgs::MotorPower::ON; //inicializamos a ON
  motor_power_publisher.publish(&power);	   // y lo publicamos
}

void loop()
{
  sensorAction(TriggerPin, EchoPin);
  nh.spinOnce();
  delay(1);
}
