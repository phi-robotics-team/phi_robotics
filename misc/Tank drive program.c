#pragma config(Hubs,  S1, MatrxRbtcs, none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_Matrix_S1_1, R_M,           tmotorMatrix, openLoop)
#pragma config(Motor,  mtr_Matrix_S1_2, L_M,           tmotorMatrix, openLoop, reversed)
#pragma config(Motor,  mtr_Matrix_S1_3, motorF,        tmotorMatrix, openLoop)
#pragma config(Motor,  mtr_Matrix_S1_4, motorG,        tmotorMatrix, openLoop)
#pragma config(Servo,  srvo_Matrix_S1_1, servo1,               tServoNone)
#pragma config(Servo,  srvo_Matrix_S1_2, servo2,               tServoNone)
#pragma config(Servo,  srvo_Matrix_S1_3, arm,                  tServoStandard)
#pragma config(Servo,  srvo_Matrix_S1_4, servo4,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                           Tele-Operation Mode Code Template
//
// This file contains a template for simplified creation of an tele-op program for an FTC
// competition.
//
// You need to customize two functions with code unique to your specific robot.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.
int deadband = 12;
task drive();
task Arm_task();
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                    initializeRobot
//
// Prior to the start of tele-op mode, you may want to perform some initialization on your robot
// and the variables within your program.
//
// In most cases, you may not have to add any code to this function and it will remain "empty".
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

void initializeRobot()
{


  return;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                         Main Task
//
// The following is the main code for the tele-op robot operation. Customize as appropriate for
// your specific robot.
//
// Game controller / joystick information is sent periodically (about every 50 milliseconds) from
// the FMS (Field Management System) to the robot. Most tele-op programs will follow the following
// logic:
//   1. Loop forever repeating the following actions:
//   2. Get the latest game controller / joystick settings that have been received from the PC.
//   3. Perform appropriate actions based on the joystick + buttons settings. This is usually a
//      simple action:
//      *  Joystick values are usually directly translated into power levels for a motor or
//         position of a servo.
//      *  Buttons are usually used to start/stop a motor or cause a servo to move to a specific
//         position.
//   4. Repeat the loop.
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
	StartTask(Arm_task);
 // servo[arm] = 0;
  //servo[arm] = 255;
	float watchedmessage;
	//int watch = 1;
	while(true)
	{
		watchedmessage = ntotalMessageCount; // grabs the number of Messages and names it watchedMessage

		wait10Msec(25); // give the Messagecount time to change it changes every 50ms

		if(watchedmessage == ntotalMessageCount) // checks to see if the Message change if has not it is Disconnected
		{                // if Disconnected it runs this
			motor[ mtr_Matrix_S1_1] = 0; // stops motor
			motor[ mtr_Matrix_S1_2] = 0;
			motor[ mtr_Matrix_S1_3] = 0;
			motor[ mtr_Matrix_S1_4] = 0;

			/*motor[mtr_S1_C4_1] = 0;
			motor[mtr_S1_C4_2] = 0;*/


 //stops task robot control task
			StopTask(drive);


			wait1Msec(10); //gives time to spot

		 //restart task incase of reconnection
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


  waitForStart();   // wait for start of tele-op phase

  while (true)
  {
  	getJoystickSettings(joystick);

	  if(abs(joystick.joy1_y1) > deadband || abs(joystick.joy1_y2) > deadband)
	  {
	  	motor[R_M] = ((joystick.joy1_y2 - deadband)*abs(joystick.joy1_y2 - deadband))/100;
	  	motor[L_M] = ((joystick.joy1_y1 - deadband)*abs(joystick.joy1_y2 - deadband))/100;
		}
		else
		{
			motor[R_M] = 0;
	  	motor[L_M] = 0;
	  }
  }
}

task Arm_task()
{
	servo[arm] = 0;
	while(true)
	{
		if(joy1Btn(1))
		{
			servo[arm] = 255;
		}

	}
}
