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
//
// This file contains a template for simplified creation of an tele-op program for an FTC
// competition.
//
// You need to customize two functions with code unique to your specific                                    robot.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include "JoystickDriver.c"	 //Include file to "handle" the Bluetooth messages.
task drive();
task Arm_task();
int deadband = 16;
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
	nMotorPIDSpeedCtrl[Arm]= mtrSpeedReg;
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

	float watchedmessage;+
	+
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

			wait1Msec(10); //gives time to spot

			StartTask(Arm_task); //restart task incase of reconnection
			StartTask(drive);

			nxtDisplayTextLine(2, "DISCONNECTED"); //displays DISCONNECTED to tell you if you are Disconnected
		}
		else//if the Message change you are connected
		{

			 nxtDisplayTextLine(2, "CONNECTED");//displays CONNECTED to tell you if everything is working

		}
	}

}

task drive()
{

	int Joy1X;
	int Joy1Xmve;
	int Joy1Y;
	int Joy1Ymve;
	int L_side_motor;
	int R_side_motor;

	float Gain2 = 0.07;
	float Gain3 = 0.1;

	while (true)
	{

		getJoystickSettings(joystick);

		Joy1X = joystick.joy1_x1;  //Variables detect the value of the joystick x and y axis.
		Joy1Y = joystick.joy1_y1;

		//This is the deadband for the y axis.
		if( (abs(Joy1Y) < deadband))
		{
			Joy1Ymve = 0;
		}
		else
		{
			if(abs(Joy1Y) > deadband) //Checks if the absolute value of the joystick y axis is grater than the deadband
				Joy1Ymve = Joy1Y - (sgn(Joy1Y) * deadband);//subtracts the deadband from the joystic value to start the power at zero
		}

		//This is the deadband for the x axis
		if( (abs(Joy1X) < deadband))
		{
			Joy1Xmve = 0;
		}
		else
		{
			if(abs(Joy1X) > deadband) //Checks if the absolute value of the joystick x axis is grater than the deadband
				Joy1Xmve = Joy1X - (sgn(Joy1X) * deadband);//subtracts the deadband from the joystic value to start the power at zero
		}

		//where the stick shaping magic happens.
		Joy1Ymve = ((Joy1Ymve * Gain2) * (abs(Joy1Ymve) * Gain3));
		Joy1Xmve = ((Joy1Xmve * Gain2) * (abs(Joy1Xmve) * Gain3));
		//this equaion can also be phrased as Y = k1X^2 + k2X.

		//Provisions for turning.
		L_side_motor = Joy1Ymve + Joy1Xmve;
		R_side_motor = Joy1Ymve - Joy1Xmve;
		//this value can be greater than |100| so greater values will need to be reduced to |100|

		if ( abs(L_side_motor) > 100)
		{
			L_side_motor = sgn(L_side_motor) * 100;

		}

		if ( abs(R_side_motor) > 100)
		{
			R_side_motor = sgn(R_side_motor) * 100;
		}

		//now we set the power of the motors.

		motor[F_L] = L_side_motor;
		motor[B_L] = L_side_motor;
		motor[F_R] = R_side_motor;
		motor[B_R] = R_side_motor;
	}
}

task Arm_task()
{

	int armPower;
	int armPower_raw;
  int limit = 75;
	float Gain2 = 0.07;
	float Gain3 = 0.1;

  while (true)
	{
		getJoystickSettings(joystick);

		armPower_raw = joystick.joy1_y2;

		if (abs(armPower_raw) > deadband)
		{
			armPower = (armPower_raw - sgn(armPower_raw * deadband));

			armPower = ((armPower * Gain2) * (abs(armPower) * Gain3));

			if(armPower > limit)
			{
				armPower = limit;
			}
			else if(armPower < -limit)
			{
				armPower = -limit;
			}
			motor[Arm] = armPower;
		}
		else
		{
			armPower = 0;
			motor[Arm] = armPower;
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

	if (joy1Btn( 7 ))
	{
		//	StopTask(drive);
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
