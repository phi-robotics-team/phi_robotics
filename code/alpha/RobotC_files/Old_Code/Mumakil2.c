#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     IR,             sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S3,     Gyro,           sensorI2CHiTechnicGyro)
#pragma config(Motor,  motorA,          Bly,           tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     Jack,          tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     Ramp,          tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     F_L,           tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     B_L,           tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     Arm,           tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     Lift,          tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     F_R,           tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C4_2,     B_R,           tmotorTetrix, PIDControl, reversed, encoder)
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
#include "Turn_Gyro.c"
#include "move2.5_452.c"

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

	motor(F_L) = 0;
	motor(B_L) = 0;
	motor(F_R) = 0;
	motor(B_R) = 0;
	nMotorEncoder[B_L]	= 0;
	nMotorEncoder[B_R]	= 0;

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
	int IRvalue = SensorValue[IR];
	wait10Msec(140);

	IRvalue = 7;

	if(IRvalue < 5 || IRvalue > 7)
	{
		IRvalue = 0;
	}
//Robot takes reading of the IR


	if(IRvalue==5)//Far
	{
		wait10Msec(25);

  	Move(52,75);
		wait10Msec(55);

		Turn(42);
		wait10Msec(55);

		Arm_move(149);
		wait10Msec(55);

		motor[Lift] = 75;
		wait10Msec(25);
		motor[Lift] = 0;

		Move(28.5,75);
		wait10Msec(55);

		Arm_move(1);
		wait10Msec(55);

		Move(-1,75);
		wait10Msec(55);

		Arm_move(1);
		wait10Msec(55);

		Move(-1,75);
		wait10Msec(55);

		Arm_move(3);
		wait10Msec(55);

		Move(-15,75);
		wait10Msec(55);

	}

	if(IRvalue==6 || IRvalue==0)//Middle
	{
         wait10Msec (55);
		Move(27,75);
		wait10Msec(55);


		Turn(51);
		wait10Msec(55);

		Arm_move(154);
		wait10Msec(55);

		motor[Lift] = 75;
		wait10Msec(32);
		motor[Lift] = 0;

		Move(42.5,80);
		wait10Msec(55);

		Arm_move(12);
		wait10Msec(55);

		Move(-15,75);
		wait10Msec(55);

  	Turn(50);
  	wait10Msec(55);

  	Move(-10,75);
  	wait10Msec(55);

	}

	if(IRvalue==7)//Close
	{
		wait10Msec(55);
		Move(4,60);
		wait10Msec(55);

		Turn(80);
		wait10Msec(55);

		Move(25,75);
		wait10Msec(55);

		Turn(-36);
		wait10Msec(55);

		Arm_move(149);
		wait10Msec(55);

		motor[Lift] = 75;
		wait10Msec(25);
		motor[Lift] = 0;

		Move(26,75);
		wait10Msec(10);

		Arm_move(22);
		wait10Msec(55);

		Move(-7,75);
		wait10Msec(55);


	}



}