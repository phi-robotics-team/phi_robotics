#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     Gyro,           sensorI2CHiTechnicGyro)
#pragma config(Sensor, S3,     IR,             sensorHiTechnicIRSeeker600)
#pragma config(Sensor, S4,     sonar,          sensorNone)
#pragma config(Motor,  mtr_S1_C1_1,     right,           tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     left,           tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     block_arm,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     Flag_Arm,      tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_1,     motorH,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     Winch,         tmotorTetrix, openLoop, reversed)
#pragma config(Servo,  srvo_S1_C4_1,    Hook,                 tServoStandard)
#pragma config(Servo,  srvo_S1_C4_2,    Claw,                 tServoStandard)
#pragma config(Servo,  srvo_S1_C4_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_6,    servo6,               tServoNone)
//Double click on the space above to write the pragma
//this program was written by Phi robotics ftc team 452 and 4322 on Fri Oct 18 13:52:09 2013
 //please give credit to the team
#include "JoystickDriver.c"  //Include file to handle the Bluetooth messages.
#include "Buttonmap.h"
int deadband = 10;
int mode = 1;
task drive();
task Arm();
 /////////////////////////////
task main()
{
  nxtDisplayTextLine(2, "Waiting for start");
	waitForStart();   // wait for start of tele-op phase
 StartTask( drive );
 StartTask( Arm );
float watchedmessage;
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
			StopTask(drive);
			StopTask( Arm );
			wait1Msec(10); //gives time to spot
			StartTask(drive);
			StartTask( Arm );
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
  int deadband = 10;
 float drivepower;
  int cut = 10;
	while (true)
	{
		getJoystickSettings(joystick);
		if(abs(joystick.joy1_y1) > deadband || abs(joystick.joy1_x1) > deadband)
		{
			if(abs(joystick.joy1_y1) > abs(joystick.joy1_x1))
			{
				drivepower = (joystick.joy1_y1/cut) * abs(joystick.joy1_y1/cut);
          if(drivepower > 100)
          {
          	drivepower = 100;
          }
          else if(drivepower < -100)
          {
          	drivepower = -100;
          }
										motor[right] =	drivepower;
					motor[left] = drivepower;
			}
			else if(abs(joystick.joy1_y1) <	 abs(joystick.joy1_x1))
			{
				drivepower = (joystick.joy1_x1/cut) * abs(joystick.joy1_x1/cut);
				if(drivepower > 100)
          {
          	drivepower = 100;
          }
          else if(drivepower < -100)
          {
          	drivepower = -100;
          }
				motor[left] =	drivepower;
								motor[right] = -1 * drivepower;
							}
			else 			{
				motor[left] =	0;
				motor[right] =	0;
				drivepower = 0;
			}
		}
		else
		{
			motor[left] =	0;
			motor[right] = 0;
			drivepower = 0;
		}
	}
}
task Arm()
{
	int armPower;
	int armPower_raw;
	int limit = 75;
	int cut = 2.5;
	float Gain2 = 0.07; //Sets the curve for the stick shaping
	float Gain3 = 0.1;

	while (true)
	{
		getJoystickSettings(joystick);

		if (mode == 1) //If in mode 1
			{
				cut = 2.5; //Motor will go normal speed
			}
		else if (mode == 2) //If in mode 2
			{
				cut = 4; //Motor will go at 62.5% speed
			}
		else //If for some reason, it's not in either mode
			{
				cut = 2.5; //Motor go at a default of normal speed
			}

		armPower_raw = joystick.joy1_y2; //Gets joystic value for 2nd y axis on the first joystick

		if (abs(armPower_raw) > deadband) //Checks if the Arm is greater than deadband
		{
			//this subtracts the deadband value form the joystick to start power at zero
			armPower = (armPower_raw - sgn(armPower_raw * deadband));

			armPower = ((armPower * Gain2) * (abs(armPower) * Gain3)); //Stick shaping magic happens here
			//This equaion can also be phrased as Y = k1X^2 + k2X.

			if (armPower > limit) //Max out the arm power at the set limit
			{
				armPower = limit;
			}
			else if (armPower < -limit)
			{
				armPower = -limit;
			}
			motor[Block_Arm] = armPower/cut; //Set the power of the motor
		}
		else //If the joystick isn't greater than the deadband
		{
			armPower = 0; //Arm power is set to zero
			motor[Block_Arm] = armPower;
		}

		if(joy1Btn( BTN_RB )) //If right bumper is pressed
		{
			if (ServoValue[Claw] == 10) //If the claw servo is open
			{
				servo[Claw] = 110; //Closes claw servo
			}
			if(ServoValue[Claw] == 110) //If the claw servo is closed
			{
				servo[Claw] = 10; //Opens claw servo
			}
		}
	if(joy1Btn(BTN_RT)) //If right trigger is pressed
	{
		servo[Claw] = 10; //Force opens arm servo
	}
}
}
