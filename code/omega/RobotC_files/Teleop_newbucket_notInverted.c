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
int mode = 1;

// *********** Include files ********

#include "JoystickDriver.c"	 //Include file to "handle" the Bluetooth messages.
//#include "turn_gyro2.c"  // Include for gyro
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
	servo[Arm] = 200; //Presets arm servo to 110
	//motor[Block_Arm] = 90;
	//wait10Msec(250);
	//motor[Block_Arm] = 0;
	// Place code here to sinitialize servos to starting positions.
	// Sensors are automatically configured and setup by ROBOTC. They may need a brief time to stabilize.
  nMotorPIDSpeedCtrl[Right_Side]= mtrSpeedReg;
	nMotorPIDSpeedCtrl[Left_Side]= mtrSpeedReg;

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

task Arm1()
{
	int armPower;
	int armDirection;
	int armPower_raw;
	int limit = 75;
	int cut = 2.5;
	float Gain2 = 0.07;
	float Gain3 = 0.1;

	while (true)
	{
		getJoystickSettings(joystick);

		if (mode == 1)
			{
				armDirection = -1;
			}
			else if (mode == 2)
				{
					armDirection = 1;
				}
				else
					{
						armDirection = -1;
					}
		armPower_raw = joystick.joy1_y2;

		if (abs(armPower_raw) > deadband)
		{
			armPower = (armPower_raw - sgn(armPower_raw * deadband));

			armPower = ((armPower * Gain2) * (abs(armPower) * Gain3));

			if (armPower > limit)
			{
				armPower = limit;
			}
			else if (armPower < -limit)
			{
				armPower = -limit;
			}
			motor[Block_Arm] = (armDirection*armPower)/cut;
		}
		else
		{
			armPower = 0;
			motor[Block_Arm] = armPower;
		}

		if(joy1Btn( BTN_RB ))
		{
			if (ServoValue[Arm] == 0) //If the arm servo is open
			{
				servo[Arm] = 200; //Closes arm servo

			}
			if(ServoValue[Arm] == 200)
			{
				servo[Arm] = 0; //
			}
		}
if(joy1Btn(BTN_RT))
{
	motor[Right_Side] = 40;
	motor[Left_Side] = 40;
	motor[Arm] = 60;
	wait10Msec(30);
	motor[Right_Side] = 0;
	motor[Left_Side] = 0;
	motor[Arm] = 0;
}
	}
}


task drive()
{
	initializeRobot();

	int Joy1X;
	int Joy1Xmve;
	int Joy1Y;
	int Joy1Ymve;
	int L_side_motor;
	int R_side_motor;
	int cut;

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
		//This equaion can also be phrased as Y = k1X^2 + k2X.

		//Provisions for turning.
		L_side_motor = Joy1Ymve - Joy1Xmve;
		R_side_motor = Joy1Ymve + Joy1Xmve;
		//This value can be greater than |100| so greater values will need to be reduced to |100|

		if ( abs(L_side_motor) > 100)
		{
			L_side_motor = sgn(L_side_motor) * 100;

		}

		if ( abs(R_side_motor) > 100)
		{
			R_side_motor = sgn(R_side_motor) * 100;
		}

		//Now we set the power of the motors.

		motor[Left_Side] = -L_side_motor/cut;
		motor[Right_Side] = -R_side_motor/cut;



		if(joy1Btn( BTN_LB ))
		{
			motor[Winch] = -50; //When left button is pressed, move winch at -50% power
		}
		else if(joy1Btn( BTN_LT ))
		{
			motor[Winch] = 50; //When left trigger is pressed, move winch at 50% power
		}
		else
		{
			motor[Winch] = 0; //If no buttons pressed, don't move winch
		}
		if(joy1Btn( BTN_X ))
		{
			servo[Hook] = 35; //If X button is pressed, move Hook servo to a value of 35
		}
		if(joy1Btn( BTN_B ))
		{
			servo[Hook] = 105; //If B button is pressed, move Hook servo to a value of 105
		}
		//	if(joy1Btn( 2 ))			// If button 2 (B) is pressed, turn wrist one way
		//{
		//if (ServoValue[Arm] > 0 && ServoValue[Arm] < 255)
		//{
		//servo[Arm] = ServoValue[Arm]-6;
		//}
		//}
		if(joy1Btn( BTN_A ))
		{
			motor[Flag_Arm] = 100;//If A button is pressed, move flag arm at 100% power
		}
		else if (joy1Btn(BTN_Y))
		{
			motor[Flag_Arm] = -100; //If Y button is pressed, move flag arm at -100% power
		}
		else
		{
			motor[Flag_Arm] = 0; //If no button is pressed, don't move Flag arm
		}
		if(joy1Btn( BTN_SELECT ))
			{
				if (mode == 1) //If in quick control mode
				{
					mode = 2; //Select button switches controls to slow controls
				}
				else if (mode == 2) //If in slow control mode
				{
					mode = 1; //Select button switches to quick controls
				}
				else
				{
					mode = 1; //Starts program in mode 1
				}
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
