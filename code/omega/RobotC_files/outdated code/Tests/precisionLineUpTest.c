#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     Gyro,           sensorI2CHiTechnicGyro)
#pragma config(Sensor, S3,     mux,            sensorI2CCustom)
#pragma config(Sensor, S4,     ir,             sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  mtr_S1_C1_1,     leftFront,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     leftRear,      tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     rightFront,    tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     rightRear,     tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     lift,          tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     intake,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C4_1,    inputstop,            tServoStandard)
#pragma config(Servo,  srvo_S1_C4_2,    hook1,                tServoStandard)
#pragma config(Servo,  srvo_S1_C4_3,    hook2,                tServoStandard)
#pragma config(Servo,  srvo_S1_C4_4,    irTurret,             tServoStandard)
#pragma config(Servo,  srvo_S1_C4_5,    ultraTurret,          tServoStandard)
#pragma config(Servo,  srvo_S1_C4_6,    output,               tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#define light msensor_S3_1
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

float avgdata = 0;
void initializeRobot()
{
	servo[hook1] = 0;
	servo[hook2] = 255;
	servo[output] = 130;
	servo[inputstop] = 235;

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

float getUltraAngle()
{
	int servoVal = 42;
	int endPos = 180;
	servo[ultraTurret] = servoVal;
	wait10Msec(100);
	int count = 0;
	while (servoVal <= endPos)
	{
		servoVal++;
		servo[ultraTurret] = servoVal;
		if (USreadDist(ultraSonic) > 20 && USreadDist(ultraSonic) < 40)
			count++;
		else
			count = 0;
		if (count > 20)
			break;
		wait10Msec(1);
	}
	if (servoVal < endPos)
		return (float)servoVal * 180.0 / 256.0;
	else
		return -1;
}

task main()
{
	initializeRobot();
	clearDebugStream();

	if (TSreadState(touch) == 1)
	{
		motor[lift] = 75;
		bool raising = false;
		nMotorEncoder[lift] = 0;
		while (abs(nMotorEncoder[lift]) <= 500)
		{
			if (TSreadState(touch) != 1 && !raising)
			{
				nMotorEncoder[lift] = 0;
				raising = true;
			}
			wait10Msec(10);
		}
		motor[lift] = 0;
	}

	float Angle = 0;
	while (true)
	{
		Angle = getUltraAngle();
		if (Angle == -1)
			Move(-5, 0.3);
		else if (Angle >= 85 && Angle <= 95)
			break;
		else
		{
			Turn(Angle - 90);
		}
	}
	Move(-((float)USreadDist(ultraSonic)/2.54 - 6), 0.25);
}