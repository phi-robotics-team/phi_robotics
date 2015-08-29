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

#include "hitechnic-sensormux.h"
#include "lego-touch.h"

task main()
{
	clearDebugStream();
	motor[lift] = 75;
	bool raising = false;
	int nxtButton = 0;
	nMotorEncoder[lift] = 0;
	while (true)
	{
		if (TSreadState(touch) != 1 && !raising)
		{
			nMotorEncoder[lift] = 0;
			raising = true;
		}
		nxtButton = nNxtButtonPressed;
		if (nxtButton == 3)
			break;
		wait10Msec(10);
	}
	writeDebugStreamLine("%d", nMotorEncoder[lift]);
	motor[lift] = 0;
}