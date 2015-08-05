#pragma config(Hubs,  S1, HTMotor,  HTServo,  none,     none)
#pragma config(Sensor, S2,     Accel,          sensorI2CCustom)
#pragma config(Motor,  mtr_S1_C1_1,     motorD,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorE,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C2_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                           Autonomous Mode Code Template
//
// This file contains a template for simplified creation of an autonomous program for an TETRIX robot
// competition.
//
// You need to customize two functions with code unique to your specific robot.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.
#include "drivers/hitechnic-accelerometer.h"
task getaccel();

int X_axis;
int Y_axis;
int Z_axis;
int X_axis_old;
int offset_X=0,offset_Y=0,offset_Z=0;
int offset=0;
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                    initializeRobot
//
// Prior to the start of autonomous mode, you may want to perform some initialization on your robot.
// Things that might be performed during initialization include:
//   1. Move motors and servos to a preset position.
//   2. Some sensor types take a short while to reach stable values during which time it is best that
//      robot is not moving. For example, gyro sensor needs a few seconds to obtain the background
//      "bias" value.
//
// In many cases, you may not have to add any code to this function and it will remain "empty".
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

void initializeRobot()
{
  // Place code here to sinitialize servos to starting positions.
  // Sensors are automatically configured and setup by ROBOTC. They may need a brief time to stabilize.

  return;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                         Main Task
//
// The following is the main code for the autonomous robot operation. Customize as appropriate for
// your specific robot.
//
// The types of things you might do during the autonomous phase (for the 2008-9 FTC competition)
// are:
//
//   1. Have the robot follow a line on the game field until it reaches one of the puck storage
//      areas.
//   2. Load pucks into the robot from the storage bin.
//   3. Stop the robot and wait for autonomous phase to end.
//
// This simple template does nothing except play a periodic tone every few seconds.
//
// At the end of the autonomous period, the FMS will autonmatically abort (stop) execution of the program.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

task main()
{
  initializeRobot();
  const float Conversion = 9.8/200;

  float time = 0;
  int X_axis_old =0;
  int Velocity = 0;
  int Velocity_old = 0;
  float Distance = 0,distation = 0;
  //int Distance_old = 0;
  int offsetagv_X = 0 ,offsetagv_Y = 0;

  float theta_X, phi_Y;

  clearDebugStream();
  for(int i = 0; i <= 20; i++)
  {
		HTACreadAllAxes(Accel, X_axis, Y_axis, Z_axis);
		offsetagv_X += abs(X_axis);
		offsetagv_Y += abs(Y_axis);
		offset_Z += abs(Z_axis);
		wait1Msec(100);
	}
	StartTask(getaccel);

	offset_X = (float) (offsetagv_X/20);
	offset_Y = (float) (offsetagv_Y/20);
	offset_Z = (float) (offset_Z/20);

	theta_X = atan((offset_X)/(sqrt((offset_Z*offset_Z)+(offset_Y*offset_Y))));
	phi_Y = atan((offset_Y)/(sqrt((offset_Z*offset_Z)+(offset_X*offset_X))));

		while(Distance <= distation)
		{
			time = time1[T1]/1000;
			Velocity = (time)*(X_axis+X_axis_old)/2+Velocity_old;
			Distance = time*(Velocity+Velocity_old)/2+Distance;
			Velocity_old += Velocity;
			wait10Msec(1);
		}

}
task getaccel()
{
	while(true)
	{
		ClearTimer(T1);
		HTACreadAllAxes(Accel, X_axis, Y_axis, Z_axis);
		X_axis = X_axis - offset_X;
		wait10Msec(1);
		X_axis_old = X_axis;
	}
}
