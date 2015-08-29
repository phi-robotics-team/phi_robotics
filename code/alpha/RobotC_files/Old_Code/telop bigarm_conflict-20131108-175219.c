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
//													 Tele-Operation Mode Code Template
//

// This file contains a template for simplified creation of an tele-op program for an FTC
// competition.
//
// You need to customize two functions with code unique to your specific robot.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include "JoystickDriver.c"	 //Include file to "handle" the Bluetooth messages.
task drive();
task drivetwo();
task Arm_task();
int deadband = 20;
//////////int gameend = 0;
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//																		initializeRobot
//
// Prior to the start of tele-op mode, you may want to perform some initialization on your robot
// and the variables within your program.
//
// In most cases, you may not have to add any code to this function and it will remain "empty".
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

void initializeRobot()
{
	nMotorPIDSpeedCtrl[B_L]= mtrSpeedReg;
	nMotorPIDSpeedCtrl[F_L]= mtrSpeedReg;
	nMotorPIDSpeedCtrl[F_R]= mtrSpeedReg;
	nMotorPIDSpeedCtrl[F_L]= mtrSpeedReg;
  //nMotorPIDSpeedCtrl[Arm]= mtrSpeedReg;
	nMaxRegulatedSpeed12V = 1000;

	return;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//																				 Main Task
//
// The following is the main code for the tele-op robot operation. Customize as appropriate for
// your specific robot.
//
// Game controller / joystick information is sent periodically (about every 50 milliseconds) from
// the FMS (Field Management System) to the robot. Most tele-op programs will follow the following
// logic:
//	 1. Loop forever repeating the following actions:
//	 2. Get the latest game controller / joystick settings that have been received from the PC.
//	 3. Perform appropriate actions based on the joystick + buttons settings. This is usually a
//			simple action:
//			*	 Joystick values are usually directly translated into power levels for a motor or
//				 position of a servo.
//			*	 Buttons are usually used to start/stop a motor or cause a servo to move to a specific
//				 position.
//	 4. Repeat the loop.
//
// Your program needs to continuously loop because you need to continuously respond to changes in
// the game controller settings.
//
// At the end of the tele-op period, the FMS will autonmatically abort (stop) execution of the program.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

task main()
{
	initializeRobot();

	bFloatDuringInactiveMotorPWM = false;
nxtDisplayTextLine(2, "Waiting for start");
	waitForStart();		// wait for start of tele-op phase
	nxtDisplayTextLine(2, "starting");
	StartTask( drive );
	StartTask( Arm_task );

	float watchedmessage;
	//int watch = 1;
	while(true)
	{
		watchedmessage = ntotalMessageCount; // grabs the number of Messages and names it watchedMessage

		wait10Msec(25); // give the Messagecount time to change it changes every 50ms

		if(watchedmessage == ntotalMessageCount) // checks to see if the Message change if has not it is Disconnected
		{                // if Disconnected it runs this
			motor[mtr_S1_C1_1] = 0; // stops motor
			motor[mtr_S1_C1_2] = 0;
			motor[mtr_S1_C2_1] = 0;
			motor[mtr_S1_C2_2] = 0;
			motor[mtr_S1_C3_1] = 0;
			motor[mtr_S1_C3_2] = 0;
			motor[mtr_S1_C4_1] = 0;
			motor[mtr_S1_C4_2] = 0;



			StopTask(Arm_task); //stops task robot control task
			StopTask(drive);
			StopTask(drivetwo);

			wait1Msec(10); //gives time to spot

			StartTask(Arm_task); //restart task incase of reconnection
			StartTask(drive);

			nxtDisplayTextLine(2, "DISCONNECTED"); //displays DISCONNECTED to tell you if you are Disconnected
		}
		else//if the Message change you are connected
		{

			nxtDisplayTextLine(2, "CONNECTED"); //displays CONNECTED to tell you if everything is working

		}
	}

}

task drive()
{

	int rampup = 50;
	int startmove = 0;


	while (true)
	{
		getJoystickSettings(joystick);

		if(abs(joystick.joy1_y1) > deadband || abs(joystick.joy1_x1) > deadband)
		{
			if(abs(joystick.joy1_y1) > abs(joystick.joy1_x1))
			{
				if(joystick.joy1_y1 < 0)
				{
					rampup = rampup * -1;
				}

				if(startmove == 0)
				{
					motor[F_L] =	rampup;
					motor[F_R] =	rampup;
					motor[B_L] = rampup;
					motor[B_R] = rampup;
					startmove = 1;
				}
				else
				{

					motor[F_L] =	joystick.joy1_y1;
					motor[F_R] =	joystick.joy1_y1;
					motor[B_L] = joystick.joy1_y1;
					motor[B_R] = joystick.joy1_y1;

				}

			}
			else if(abs(joystick.joy1_y1) <	 abs(joystick.joy1_x1))
			{
				motor[F_L] =	joystick.joy1_x1;
				motor[F_R] =	-joystick.joy1_x1;
				motor[B_L] = joystick.joy1_x1;
				motor[B_R] = -joystick.joy1_x1;
			}
			else //if(abs(joystick.joy1_y1) < deadband || abs(joystick.joy1_x1) < deadband)
			{
				motor[F_L] =	0;
				motor[F_R] =	0;
				motor[B_L] = 0;
				motor[B_R] = 0;
				startmove = 0;
				rampup = 50;
			}
		}

		else
		{
			motor[F_L] =	0;
			motor[F_R] =	0;
			motor[B_L] = 0;
			motor[B_R] = 0;
			startmove = 0;
			rampup = 50;
		}
	}
	if(joy1Btn( 8 ))
	{
		StartTask(drive);
	}
}

task Arm_task()
{

	int driveswitch =0;

	while (true)
	{

	 getJoystickSettings(joystick);
		if(abs(joystick.joy1_y2) > deadband)
		{

			motor[Arm] = joystick.joy1_y2/3;

		}
		else
		{
			motor[Arm] = 0;
		}


		if(joy1Btn(3))
		{
				motor[Ramp] = 100;
				wait10Msec(4);

				motor[Ramp] =0;
		}


		if(joy1Btn(2))
		{
			while(joy1Btn(2))
			{
				motor[Lift] = 100;
			}
		}

		if(joy1Btn(4))
		{
			while(joy1Btn(4))
			{
				motor[Lift] = -100;
			}
		}

		motor[Lift] = 0;
		if (joy1Btn(3) && driveswitch==0)
		{
			StopTask(drive);
			StartTask(drivetwo);
			driveswitch=1;
		}
		else if(joy1Btn(3)&& driveswitch==1)
		{
			StopTask(drivetwo);
			StartTask(drive);
			driveswitch=0;
		}
		if (joy1Btn( 7 ))
		{
			StopTask(drive);
			while(joy1Btn( 7 ))
			{
				motor[Jack] = 75;

			}
		}
		if(joy1Btn( 5 ))
		{
			while(joy1Btn( 5 ))
			{
				motor[Jack] = -75;

			}

		}
				motor[Ramp] = 0;



	}
}

task drivetwo()
{
	int rampup = 25;
	int startmove = 0;


	while (true)
	{
		getJoystickSettings(joystick);

		if(abs(joystick.joy1_y1) > deadband || abs(joystick.joy1_x1) > deadband)
		{
			if(abs(joystick.joy1_y1) > abs(joystick.joy1_x1))
			{
				if(joystick.joy1_y1 < 0)
				{
					rampup = rampup * -1;
				}

				if(startmove == 0)
				{
					motor[F_L] =	rampup;
					motor[F_R] =	rampup;
					motor[B_L] = rampup;
					motor[B_R] = rampup;
					startmove = 1;
				}
				else
				{

					motor[F_L] =	joystick.joy1_y1/2;
					motor[F_R] =	joystick.joy1_y1/2;
					motor[B_L] = joystick.joy1_y1/2;
					motor[B_R] = joystick.joy1_y1/2;

				}

			}
			else if(abs(joystick.joy1_y1) <	 abs(joystick.joy1_x1))
			{
				motor[F_L] =	joystick.joy1_x1/2;
				motor[F_R] =	-joystick.joy1_x1/2;
				motor[B_L] = joystick.joy1_x1/2;
				motor[B_R] = -joystick.joy1_x1/2;
			}
			else //if(abs(joystick.joy1_y1) < deadband || abs(joystick.joy1_x1) < deadband)
			{
				motor[F_L] =	0;
				motor[F_R] =	0;
				motor[B_L] = 0;
				motor[B_R] = 0;
				startmove = 0;
				rampup = 25;
			}
		}

		else
		{
			motor[F_L] =	0;
			motor[F_R] =	0;
			motor[B_L] = 0;
			motor[B_R] = 0;
			startmove = 0;
			rampup = 25;
		}
	}
	if(joy1Btn( 8 ))
	{
		StartTask(drive);
	}
}