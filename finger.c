*
 * sweep.c,  7 Dec 14
 * DJ
 * resin.io hackathon
 */

// Based on ideas from: Sweep
// by BARRAGAN <http://barraganstudio.com> 


#include <Servo.h> 

// Pin numbers used to control a servo have to have a ~ next to them!!
#define l_pin 3
#define s_pin 5

// max/min serveo angles are 0/180
// Picked 60 as our horizontal position
#define arm_zero_pos 60
#define s_final_pull_angle 90
// Should be -45, but for some reason the servo is reversed???
#define l_lift_pos (arm_zero_pos+45)

#define l_init_pos arm_zero_pos
#define s_init_pos arm_zero_pos

 
// 'large' and 'small' servo
Servo l_myservo;  // create long servo object
Servo s_myservo;  // create short servo object
                  // a maximum of eight servo objects can be created 

// Adding a small delay between all operations makes things work more reliably 
void setup() 
{ 
  l_myservo.attach(l_pin);  // attach the long servo on a pin
delay(50);
  s_myservo.attach(s_pin);  // attach the short servo on a pin
} 
 
// Straighten a finger
void straight_finger(void)
{
delay(50);
s_myservo.write(s_init_pos);              // tell servo to go to position in variable 'pos' 
delay(50);
l_myservo.write(l_init_pos);              // tell servo to go to position in variable 'pos' 
}


void pull_forward(void)
{
int pull_inc =s_final_pull_angle/3;

delay(50);
s_myservo.write(arm_zero_pos+pull_inc);      // tell servo to go to position in variable 'pos' 
delay(50);
s_myservo.write(arm_zero_pos+2*pull_inc);      // tell servo to go to position in variable 'pos' 
delay(50);
s_myservo.write(arm_zero_pos+3*pull_inc);      // tell servo to go to position in variable 'pos' 
}

void lift_long(void)
{
delay(50);
l_myservo.write(l_lift_pos);      // tell servo to go to position in variable 'pos' 
}

void reset_finger(void)
{
lift_long();
straight_finger();
}

 
void loop() 
{ 
reset_finger();
delay(50);
while (1)
   {
// The theory is that for a hand to pull itself forward the short part of
// the finger rotates down and 'back'.
// The long part of the finger lifts up, short part then straightens and whole
// finger drops to 'neutral'.
   reset_finger();
   delay(750);
   pull_forward();
   delay(250);
   }

} 


