#pragma config(Hubs,  S1, HTServo,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Sensor, S2,     Gyro,           sensorI2CHiTechnicGyro)
#pragma config(Motor,  mtr_S1_C2_1,     rightFront,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     rightRear,     tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     lift,          tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     intake,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     leftFront,     tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C4_2,     leftRear,      tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Servo,  srvo_S1_C1_1,    output,               tServoStandard)
#pragma config(Servo,  srvo_S1_C1_2,    hook1,                tServoStandard)
#pragma config(Servo,  srvo_S1_C1_3,    hook2,                tServoStandard)
#pragma config(Servo,  srvo_S1_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_6,    servo6,               tServoNone)
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

float GyroBias = 0;
#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.
#include "newMove.c"
#include "turn_gyro_2_wheel.c"


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

float avgdata = 0;
void initializeRobot()
{
  servo[hook1] = 255;
	servo[hook2] = 0;

	for (int i = 0; i < 20; i++)
	{
		avgdata += SensorValue[Gyro];
		wait1Msec(25);
	}
	GyroBias = ((float)avgdata / 20);

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

  waitForStart(); // Wait for the beginning of autonomous phase.
  clearDebugStream();
  //leave zone
	Move(-9.66, 1);
	wait10Msec(10);
	Turn(23.24);
	wait10Msec(10);
	Move(-51.51, 1);
	wait10Msec(10);
	Turn(-21.09);
	wait10Msec(10);
	Move(-44.36, 1);
	//grab goal
	wait10Msec(30);
  servo[hook1] = 0;
	servo[hook2] = 255;
	wait10Msec(30);
	Turn(-1.97);
	wait10Msec(10);
	Move(110.33, 1);
	wait10Msec(10);
	Turn(-88.21);
	wait10Msec(10);
	Move(-39.02, 1);
	wait10Msec(10);
	//score
	motor[lift] = 75;
	wait10Msec(800);
	motor[lift] = 0;
	wait10Msec(10);
	servo[output] = 250;
	wait10Msec(500);
	//release goal
	servo[hook1] = 255;
	servo[hook2] = 0;
	wait10Msec(300);
	Move(5, 1);
	wait10Msec(30);
	Turn(90);
}
