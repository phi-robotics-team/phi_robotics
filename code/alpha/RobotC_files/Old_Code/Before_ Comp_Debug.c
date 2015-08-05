#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S2,     IR,             sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S3,     Gyro,           sensorI2CHiTechnicGyro)
#pragma config(Sensor, S4,     SONAR_1,        sensorI2CCustom)
#pragma config(Motor,  motorB,          Flag1,         tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,          Flag2,         tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     L_Motor,       tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     R_Motor,       tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     Arm,           tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     Block_Sweep,   tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_1,     Winch,         tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     Flag_Raiser,   tmotorTetrix, openLoop, reversed)
#pragma config(Servo,  srvo_S1_C4_1,    Bucket_Release,       tServoStandard)
#pragma config(Servo,  srvo_S1_C4_2,    Spring_Release,       tServoStandard)
#pragma config(Servo,  srvo_S1_C4_3,    Block_Chuck,          tServoStandard)
#pragma config(Servo,  srvo_S1_C4_4,    IRS_1,                tServoNone)
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
//task Arm_hold;
#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.nclude "Move.c"
#include "drivers/hitechnic-sensormux.h"
#include "drivers/hitechnic-accelerometer.h"
#include "drivers/hitechnic-sensormux.h"
#include "drivers/lego-ultrasound.h"

bool Hold_enable = false;
bool Scan = false;




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
	while(true)
	{
		bDisplayDiagnostics = false;// Wait for the beginning of autonomous phase.
		eraseDisplay();
		setBluetoothOff();
		//	WriteShort(hFileHandle, nIoResult, nParm);


		if ( externalBatteryAvg < 0)

		{
		while (externalBatteryAvg < 0)
		{
			eraseDisplay();
			nxtDisplayTextLine(1, "Ext Batt: OFF");       //External battery is off or not connected
			nxtDisplayCenteredBigTextLine(1, "What!?");
			nxtDisplayTextLine(3, "My name is,");
			nxtDisplayTextLine(4, "Iego Montoya,");
			nxtDisplayTextLine(5, "you did not turn");
			nxtDisplayTextLine(6, "on the robot");
			nxtDisplayTextLine(7, "NOW YOU DIE");
			nxtDisplayTextLine(8, "YOU COCKROACH!!!!!!");
			PlayImmediateTone(600, 20);
			PlayImmediateTone(400, 20);
			wait10Msec(20);
		}
		}
		else
		{
			nxtDisplayTextLine(1, "Ext Batt:%4.1f V", externalBatteryAvg / (float) 1000);
		}
		while ( externalBatteryAvg / (float) 1000 < 13 && externalBatteryAvg / (float) 1000 > 0 || nAvgBatteryLevel / (float) 1000 < 7)
		{
			eraseDisplay();

			nxtDisplayBigTextLine(6, "Battery");
			nxtScrollText("poopheads");
			nxtScrollText("You didnt change the battery you shmuts!");
			nxtScrollText("the battery you");
			nxtScrollText("shmuts!");
			PlayImmediateTone(600, 70);
			PlayImmediateTone(400, 70);
			wait10Msec(20);
		}

		nxtDisplayTextLine(2, "NXT Batt:%4.1f V", nAvgBatteryLevel / (float) 1000);   // Display NXT Battery Voltage
		nxtDisplayTextLine(3, "R = %d L = %d", nMotorEncoder[R_Motor], nMotorEncoder[L_Motor]);
		nxtDisplayTextLine(4, "SONAR_1 = %d", USreadDist(SONAR_1));
		nxtDisplayTextLine(5, "IR = %d", SensorValue[IR]);
		nxtDisplayTextLine(6, "Gyro = %d", SensorValue[Gyro]);


		wait10Msec(20);
	}//End of While
	//Actuation tests.
	motor[R_Motor] = 100;
	wait10Msec(30);

	motor[R_Motor] = 0;
	wait10Msec(30);

	motor[L_Motor] = 100;
	wait10Msec(30);

	motor[L_Motor] = 0;
	wait10Msec(30);

	motor[Flag_Raiser] = 100;
	wait10Msec(30);

	motor[Flag_Raiser] = 0;
	wait10Msec(20);

	motor[Winch] = 100;
	wait10Msec(30);

	motor[Winch] = 0;
	wait10Msec(30);

	motor[Arm] = 100;
	wait10Msec(30);

	motor[Arm] = 0;
	wait10Msec(30);

	motor[Block_Sweep] = 100;
	wait10Msec(30);

	motor[Block_Sweep] = 0;
	wait10Msec(30);

	servo[Bucket_Release] = 100;
	wait10Msec(30);

	servo[Bucket_Release] = 0;
	wait10Msec(30);

	servo[Spring_Release] = 100;
	wait10Msec(30);

	servo[Spring_Release] = 0;
	wait10Msec(30);

	servo[IRS_1] = 100;
	wait10Msec(30);

	servo[IRS_1] = 0;
	wait10Msec(30);

}
