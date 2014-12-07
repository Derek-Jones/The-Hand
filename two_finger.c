/*
 * two_finger.c,  7 Dec 14
 * DJ
 * resin.io hackathon
 */

// Based on ideas from: Sweep
// by BARRAGAN <http://barraganstudio.com> 


#include <Servo.h> 

#define Lind 0
#define Sind 1
// Pin numbers used to control a servo have to have a ~ next to them!!
#define Lr_pin 3
#define Sr_pin 5
#define Ll_pin 6
#define Sl_pin 9

// max/min servo angles are 0/180
// Picked 90 as our horizontal position
#define arm_zero_pos 90
#define sL_final_pull_angle 81
// Should be -45, but for some reason the servo is reversed???
#define lL_lift_pos 45

#define l_init_pos arm_zero_pos
#define s_init_pos arm_zero_pos

typedef Servo finger_t[2];
 
// 'large' and 'small' servo
finger_t R_myservo;  // create right finger
finger_t L_myservo;  // create left finger
                  // a maximum of eight servo objects can be created 

// Adding a small delay between all operations makes things work more reliably 
void setup() 
{ 
  R_myservo[Lind].attach(Lr_pin);  // attach the long servo on a pin
delay(50);
  R_myservo[Sind].attach(Sr_pin);  // attach the short servo on a pin
delay(50);
  L_myservo[Lind].attach(Ll_pin);  // attach the long servo on a pin
delay(50);
  L_myservo[Sind].attach(Sl_pin);  // attach the short servo on a pin
} 
 
// Straighten a finger
void straight_finger(Servo myservo[2])
{
delay(50);
myservo[Sind].write(s_init_pos);              // tell servo to go to position in variable 'pos' 
delay(50);
myservo[Lind].write(l_init_pos);              // tell servo to go to position in variable 'pos' 
}


void pull_forward(Servo myservo[2], int pull_angle)
{
int pull_inc =pull_angle/3;

delay(50);
myservo[Sind].write(arm_zero_pos+pull_inc);      // tell servo to go to position in variable 'pos' 
delay(50);
myservo[Sind].write(arm_zero_pos+2*pull_inc);      // tell servo to go to position in variable 'pos' 
delay(50);
myservo[Sind].write(arm_zero_pos+3*pull_inc);      // tell servo to go to position in variable 'pos' 
}

void lift_long(Servo myservo[2], int lift_pos)
{
delay(50);
myservo[Lind].write(arm_zero_pos+lift_pos);      // tell servo to go to position in variable 'pos' 
}

void reset_finger(Servo myservo[2], int lift_pos)
{
lift_long(myservo, lift_pos);
straight_finger(myservo);
}

 
void loop() 
{ 
reset_finger(R_myservo, -lL_lift_pos);
reset_finger(L_myservo, lL_lift_pos);
delay(50);
while (1)
   {
// The theory is that for a hand to pull itself forward the short part of
// the finger rotates down and 'back'.
// The long part of the finger lifts up, short part then straightens and whole
// finger drops to 'neutral'.
   reset_finger(R_myservo, -lL_lift_pos);
   reset_finger(L_myservo, lL_lift_pos);
   delay(750);
   pull_forward(R_myservo, -sL_final_pull_angle);
   pull_forward(L_myservo, sL_final_pull_angle);
   delay(250);
   }

} 

