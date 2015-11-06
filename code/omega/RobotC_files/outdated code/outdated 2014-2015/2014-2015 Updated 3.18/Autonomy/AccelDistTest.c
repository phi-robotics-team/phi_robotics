#pragma config(Hubs,  S1, HTMotor,  none,     none,     none)
#pragma config(Sensor, S2,     gyro,           sensorI2CHiTechnicGyro)
#pragma config(Sensor, S3,     accel,          sensorI2CCustom)
#pragma config(Motor,  mtr_S1_C1_1,     rightDrive,    tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     leftDrive,     tmotorTetrix, openLoop, reversed, encoder)
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
#include "JoystickDriver.c" //Include file to "handle" the Bluetooth messages.
#include "hitechnic-accelerometer.h"

int offset = 0;

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

float convertedAccel(int rawAccel)
{
	return ((rawAccel - offset) / 200) * 9.8;
}

task main()
{
	initializeRobot(); //Executes all code in the initializeRobot() function

	int xRaw, yRaw, zRaw = 0;

	float xAccel = 0;

	int timeOld, timeNew = 0;
	float deltaTime = 0;

	float velocityOld = 0;

	float dist = 0;

	int accelBias = 0;
	for (int i = 0; i < 20; i++)
	{
		HTACreadAllAxes(accel, xRaw, yRaw, zRaw);

		accelBias += xRaw;
	}
	offset = accelBias/20;
	clearDebugStream();
	ClearTimer(T1);
	timeOld = time1[T1];
	while (true)
	{
		timeNew = time1[T1];
		deltaTime = (timeNew - timeOld) * 0.001;
		HTACreadAllAxes(accel, xRaw, yRaw, zRaw);

		xAccel = convertedAccel(xRaw);

		dist += (velocityOld * deltaTime) + (0.5 * xAccel * deltaTime * deltaTime);
		writeDebugStreamLine("%f", dist);

		velocityOld += xAccel * deltaTime;

		timeOld = timeNew;
		wait1Msec(10);
	}
}