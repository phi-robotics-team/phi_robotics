#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     Gyro,           sensorI2CHiTechnicGyro)
#pragma config(Sensor, S3,     mux,            sensorI2CCustom)
#pragma config(Sensor, S4,     htspb,          sensorI2CCustom)
#pragma config(Motor,  mtr_S1_C1_1,     leftFront,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     leftRear,      tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     intake,        tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     rightRear,     tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     rightFront,    tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_2,     lift,          tmotorTetrix, openLoop, encoder)
#pragma config(Servo,  srvo_S1_C4_1,    inputstop,            tServoStandard)
#pragma config(Servo,  srvo_S1_C4_2,    hook1,                tServoStandard)
#pragma config(Servo,  srvo_S1_C4_3,    hook2,                tServoStandard)
#pragma config(Servo,  srvo_S1_C4_4,    irTurret,             tServoStandard)
#pragma config(Servo,  srvo_S1_C4_5,    ultraTurret,          tServoStandard)
#pragma config(Servo,  srvo_S1_C4_6,    output,               tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#define ir msensor_S3_1
#define touch msensor_S3_2
#define accel msensor_S3_3
#define ultraSonic msensor_S3_4
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
#include "hitechnic-sensormux.h"
#include "hitechnic-accelerometer.h"
#include "hitechnic-irseeker-v2.h"
#include "lego-touch.h"
#include "lego-light.h"
#include "lego-ultrasound.h"

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
	clearDebugStream();
  int countsperinch = 414
  ,count;
  int distance = 5;

  count = countsperinch * distance;
//	bool raising = false;
	nMotorEncoder[lift] = 0;
	nMotorEncoder[intake] = 0;
		motor[lift] = 75;

	while(abs(count) > 	abs(nMotorEncoder[lift]))
	{

	}

/*	for(int i = 0; i < 11; i++)
	{
	//	writeDebugStreamLine("%d    %d", nMotorEncoder[intake],nMotorEncoder[lift]);
		wait10Msec(50);
	}*/



	motor[lift] = 0;
}