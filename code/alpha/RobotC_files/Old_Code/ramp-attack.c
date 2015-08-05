#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S2,     IR,             sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S3,     Gyro,           sensorI2CHiTechnicGyro)
#pragma config(Motor,  motorB,          Flag1,         tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,          Flag2,         tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     R_Motor,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     L_Motor,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     Lift,          tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     Winch,         tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_1,     Arm,           tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     Block_Sweep,   tmotorTetrix, openLoop, reversed)
#pragma config(Servo,  srvo_S1_C4_1,    Bucket_Release,       tServoStandard)
#pragma config(Servo,  srvo_S1_C4_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_6,    servo6,               tServoNone)
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
int avgdata = 0;
#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.nclude "Move.c"
#include "arm2.c"
#include "turn-gyro.c"
#include "move-3-452.c"

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
	// Take 20 readings of the gyro and average them out
	for (int i = 0; i < 20; i++) {
		avgdata += SensorValue[Gyro];
		wait1Msec(25);
	}
	// Store new bias
	GyroBias = ((float)avgdata / 20);

	int nDelay = 200;

	bFloatDuringInactiveMotorPWM = false;
	motor(R_Motor) = 0;
	motor(L_Motor) = 0;
	nMotorEncoder[R_Motor]	= 0;
	nMotorEncoder[L_Motor]	= 0;

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

	Move(10,75);
	wait10Msec(55);

	Turn(55);
	wait10Msec(55);

	Move(10, 75);
	wait10Msec(55);
}
