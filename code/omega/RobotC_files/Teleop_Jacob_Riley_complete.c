#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     Gyro,           sensorI2CHiTechnicGyro)
#pragma config(Sensor, S3,     IR,             sensorHiTechnicIRSeeker600)
#pragma config(Sensor, S4,     sonar,          sensorNone)
#pragma config(Motor,  mtr_S1_C1_1,     Right_Side,    tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     Left_Side,     tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     Block_Arm,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     Flag_Arm,      tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_1,     motorH,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     Winch,         tmotorTetrix, openLoop, reversed)
#pragma config(Servo,  srvo_S1_C4_1,    Hook,                 tServoStandard)
#pragma config(Servo,  srvo_S1_C4_2,    Arm,                  tServoStandard)
#pragma config(Servo,  srvo_S1_C4_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// ***********	Globals *********

int deadband = 10;

// *********** Include files ********

#include "JoystickDriver.c"	 //Include file to "handle" the Bluetooth messages.
#include "turn_gyro2.c"  // Include for gyro
#include "Buttonmap.h"

// *********** Prototypes ********
task drive();
//task main ();
task Arm1  ();
//task EndGame();


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
	servo[Arm] = 50;
	// Place code here to sinitialize servos to starting positions.
	// Sensors are automatically configured and setup by ROBOTC. They may need a brief time to stabilize.

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

task Arm1()
{
	int deadband = 10;
	while(true)
	{
		getJoystickSettings(joystick);

		if(abs(joystick.joy1_y2) > deadband) {
			while(abs(joystick.joy1_y2) > deadband)
			{
				getJoystickSettings(joystick);
				motor [Block_Arm] = joystick.joy1_y2/3;
			}
		}
		if(joy1Btn( BTN_RB ))			// If button 3 (B) is pressed, turn wrist one way
		{
			if (ServoValue[Arm] == 50)
			{

				servo[Arm] = 102;
			}
		}
		if(joy1Btn(BTN_LB))
		{
			if(ServoValue[Arm] == 102)
			{
				servo[Arm] = 50;
			}
		}

	}
}

task drive()
{
	initializeRobot();
	int rampup = 50;
	int startmove = 0;
	int deadband = 10;
	waitForStart();   // wait for start of tele-op phase

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

					motor[Left_Side] = rampup;
					motor[Right_Side] = rampup;
					startmove = 1;
				}
				else
				{

					motor[Left_Side] = -joystick.joy1_y1;
					motor[Right_Side] = -joystick.joy1_y1;

				}

			}
			else if(abs(joystick.joy1_y1) <	 abs(joystick.joy1_x1))
			{

				motor[Left_Side] = -joystick.joy1_x1;
				motor[Right_Side] = joystick.joy1_x1;
			}
			else //if(abs(joystick.joy1_y1) < deadband || abs(joystick.joy1_x1) < deadband)
			{

				motor[Left_Side] = 0;
				motor[Right_Side] = 0;
				startmove = 0;
				rampup = 50;
			}
		}

		else
		{

			motor[Left_Side] = 0;
			motor[Right_Side] = 0;
			startmove = 0;
			rampup = 50;


		}

		if(joy1Btn( BTN_A ))
		{
			motor[Winch] = 30;
		}
		else
		{
			motor[Winch] = 0;
		}
		if(joy1Btn( BTN_X ))			// If button 3 (B) is pressed, turn wrist one way
		{
				servo[Hook] = 35;
		}
		if(joy1Btn( BTN_B ))			// If button 3 (B) is pressed, turn wrist one way
		{
				servo[Hook] = 105;
		}
		//	if(joy1Btn( 2 ))			// If button 2 (B) is pressed, turn wrist one way
		//{
		//if (ServoValue[Arm] > 0 && ServoValue[Arm] < 255)
		//{
		//servo[Arm] = ServoValue[Arm]-6;
		//}
		//}
		if(joy1Btn( BTN_Y ))    // If button 4 (y) is pressed
		{
			motor[Flag_Arm] = 50;
		}
		else
		{
			motor[Flag_Arm] = 0;
		}

	}
}


task main()
{
	waitForStart();	 // wait for start of tele-op phase

	StartTask( drive );
	StartTask( Arm1 );
	//StartTask(main);

	float watchedmessage;
	int watch = 1;
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


			StopTask(main); //stops task robot control task
			StopTask(drive);

			wait1Msec(10); //gives time to spot

			StartTask(main); //restart task incase of reconnection
			StartTask(drive);

			nxtDisplayTextLine(2, "DISCONNECTED"); //displays DISCONNECTED to tell you if you are Disconnected
		}
		else//if the Message change you are connected
		{

			nxtDisplayTextLine(2, "CONNECTED"); //displays CONNECTED to tell you if everything is working

		}
	}

}