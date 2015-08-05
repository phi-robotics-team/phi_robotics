#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     Gyro,           sensorI2CHiTechnicGyro)
#pragma config(Sensor, S3,     IR,             sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S4,     Ultrasonic,     sensorSONAR)
#pragma config(Motor,  motorA,          Ramp_R,        tmotorNXT, openLoop)
#pragma config(Motor,  motorB,          Ramp_L,        tmotorNXT, openLoop)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     R_Front,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorE,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     Arm_motor,     tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     L_Front,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_1,     L_Rear,        tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     R_Rear,        tmotorTetrix, openLoop, encoder)
#pragma config(Servo,  srvo_S1_C4_1,    Ramp,                 tServoStandard)
#pragma config(Servo,  srvo_S1_C4_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_6,    servo6,               tServoNone)

//#pragma platform(FTC)         // Only works for "FTC" platform. Generate error on other platforms.
//#pragma systemFile            // This eliminates warning for "unreferenced" functions

   // Fastest the bot will move while seeking IR emitter
// #define MAX_SPEED 100           // Speed bot moves during sprints
// #define COUNTS_PER_DEGREE 28    // Encoder counts per degree of rotation

// VERSION 2.2

float GyroBias = 0;
int avgdata = 0;

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.
#include "move.c"
#include "turn_gyro.c"
#include "arm.c"
#include "Start.c"



void initializeRobot()
{
   // Take 20 readings of the gyro and average them out
  for (int i = 0; i < 20; i++) {
    avgdata += SensorValue[Gyro];
    wait1Msec(25);
  }
  // Store new bias
  GyroBias = ((float)avgdata / 20);

  int nDelay = 200;

  bFloatDuringInactiveMotorPWM = false;

  motor(L_Front) = 0;
  motor(L_Rear) = 0;
  motor(R_Front) = 0;
  motor(R_Rear) = 0;
  nMotorEncoder[L_Rear]	= 0;
  nMotorEncoder[R_Rear]	= 0;
  nMotorEncoder[Arm_motor]	= 0;

   return;
}


//=============================================================================
// Function: aim()
//
// Description:
//    This function will aim the robot at the IR emitter using the IR seeker
// sector 4 of the IR seeker must be alighed with ball shooter
//
//=============================================================================
void aim(int IRTarget)
{
  int MAX_IR_SPEED = 60;
  bool aimValidate = true;

     while (SensorValue[IR] != IRTarget)

     {
      nxtDisplayCenteredBigTextLine(4, "%d", SensorValue[IR]);

      if(nPgmTime >  8000)
      {
        aimValidate = false;
        break;
      }

      /*if(SensorValue[IR] < 1)
      {
        aimValidate = false;
        break;
      }*/
      if (SensorValue[IR] < IRTarget)
      {
        motor[L_Front] = MAX_IR_SPEED; // looking from the top, left side moves back, right
        motor[R_Front] = -MAX_IR_SPEED; // side moves forward for CCW rotation
        motor[L_Rear] = MAX_IR_SPEED;  // IR emitter is to the left of bot
        motor[R_Rear] = -MAX_IR_SPEED;
      }
      if (SensorValue[IR] > IRTarget)
      {
        motor[L_Front] = -MAX_IR_SPEED; // looking from the top, left side forward, right
        motor[R_Front] = MAX_IR_SPEED; // side moves back for CW rotation
        motor[L_Rear] = -MAX_IR_SPEED; // IR emitter is to the right of bot
        motor[R_Rear] = MAX_IR_SPEED;
      }
    } // end of while loop

    motor[L_Front] = 0; // since we are now pointed at the emitter, stop motors
    motor[R_Front] = 0; //
    motor[L_Rear] = 0;
    motor[R_Rear] = 0;
    wait10Msec(20);  // wait for bot to actually stop turning

}



task main()
{
	initializeRobot();
	int IRvalue = SensorValue[IR];
	Start();

   IRvalue = SensorValue[IR];
   int i;
   for (i=0;i<100;i++)
 {
   nxtDisplayCenteredBigTextLine(4, "%d", IRvalue);
 }

   if(IRvalue==1)
	{

	 Move(20.0, 70.0);    // drive forward 15 inches
   wait10Msec(10);

   Turn_gyro(90.0);     // turn counterclockwise 35 degrees
   wait10Msec(10);

   Move(26.0, 70.0);    // drive forward 24 inches
   wait10Msec(10);
   }

  else if(IRvalue==2 || IRvalue==0)
	{

   Move(15.0, 70.0);    // drive forward 15 inches
   wait10Msec(10);

   Turn_gyro(45.0);     // turn counterclockwise 35 degrees
   wait10Msec(10);

   Move(12.0, 70.0);    // drive forward 24 inches
   wait10Msec(10);
	}

	else if(IRvalue==3)
	{

	 Move(15.0, 70.0);    // drive forward 15 inches
   wait10Msec(10);

   //Turn_gyro(30.0);     // turn counterclockwise 35 degrees
   //wait10Msec(10);

   Move(12.0, 70.0);    // drive forward 24 inches
   wait10Msec(10);

}

   /*Arm(205.0, 70.0);    // arm down 205 degrees
   wait10Msec(100);*/

   aim(4);
   wait10Msec(100);

   /*Move(6.0, 70.0);    // drive forward 6 inches
   wait10Msec(10);*/

   aim(5);
   wait10Msec(100);

   aim(4);
   wait10Msec(100);

   /*Arm(-50.0, 70.0);    // arm move 50 degrees
   wait10Msec(100);

   Move(-18.0, 70.0);    // drive backward 18 inches
   wait10Msec(10);*/


}
