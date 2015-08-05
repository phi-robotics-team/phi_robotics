#pragma config(Hubs,  S1, HTServo,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Sensor, S2,     Gyro,           sensorI2CHiTechnicGyro)
#pragma config(Sensor, S3,     htspb,          sensorNone)
#pragma config(Sensor, S4,     ir,             sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  mtr_S1_C2_1,     rightFront,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     rightRear,     tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     lift,          tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     intake,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     leftFront,     tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C4_2,     leftRear,      tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Servo,  srvo_S1_C1_1,    inputstop,            tServoStandard)
#pragma config(Servo,  srvo_S1_C1_2,    hook1,                tServoStandard)
#pragma config(Servo,  srvo_S1_C1_3,    hook2,                tServoStandard)
#pragma config(Servo,  srvo_S1_C1_4,    irTurret,             tServoStandard)
#pragma config(Servo,  srvo_S1_C1_5,    ulraservo,            tServoStandard)
#pragma config(Servo,  srvo_S1_C1_6,    output,               tServoStandard)
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
float checkD = 9;

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
	servo[output] = 130;
	servo[irTurret] = 230;

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
float getIrAngle()
{
	int servoVal = 72;
	servo[irTurret] = servoVal;
	wait10Msec(100);
	int irPrev = SensorValue[ir];
	while (ServoValue[irTurret] <= 255)
	{
		servoVal++;
		servo[irTurret] = servoVal;
		//writeDebugStreamLine("IR: %d", SensorValue[ir]);
		if (SensorValue[ir] == 4 || (SensorValue[ir] == 0 && irPrev == 5))
			break;
		irPrev = SensorValue[ir];
		wait10Msec(1);
	}
	return (float)servoVal * 180.0 / 256.0;
}

task main()
{
	initializeRobot();

	//waitForStart(); // Wait for the beginning of autonomous phase.
	clearDebugStream();
	if (SensorValue[ir] == 7)
	{
		Move(-30, 0.5);
		motor[lift] = 100;
		while (true)
		{
			writeDebugStreamLine("%f", nMotorEncoder[lift]);
			wait10Msec(10);
		}
		motor[lift] = 0;
	}
	/*else
	{
		Move(-5, 0.5);
		Turn(120);
		Move(40, 0.7);
		//IR Seek
		float angle1 = 180 - getIrAngle();
		writeDebugStreamLine("Angle 1: %f", angle1);
		Move(-checkD, 0.5);
		float angle2 = getIrAngle();
		writeDebugStreamLine("Angle 2: %f", angle2);
		Move(0.5*checkD, 0.5);
		writeDebugStreamLine("Check: %f", getIrAngle());
		float beaconAngle = 0.5 * (180 - (angle1 + angle2));
		float turnAngle = 180 - (angle1 + beaconAngle);
		float distance = abs((0.5 * checkD * sinDegrees(angle1))/sinDegrees(beaconAngle));
		writeDebugStreamLine("Distance: %f", distance);
		writeDebugStreamLine("Turn: %f", turnAngle);
		Turn(-(angle2));
		Move(-(distance - 6.5), 0.8);
	}*/
	while (true){}
}
