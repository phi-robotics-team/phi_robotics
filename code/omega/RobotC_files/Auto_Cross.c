#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S2,     Gyro,           sensorI2CHiTechnicGyro)
#pragma config(Sensor, S3,     IR,             sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  motorA,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorB,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     R_Rear,        tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     L_Rear,        tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     L_Front,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     R_Front,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     Arm_Lift,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     Arm_motor,     tmotorTetrix, PIDControl, encoder)
#pragma config(Servo,  srvo_S1_C4_1,    Claw_spin,            tServoStandard)
#pragma config(Servo,  srvo_S1_C4_2,    Ramp_1,               tServoStandard)
#pragma config(Servo,  srvo_S1_C4_3,    Claw_open,            tServoStandard)
#pragma config(Servo,  srvo_S1_C4_4,    Ramp_2,               tServoStandard)
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

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.
#include "move.c"
#include "turn_gyro.c"
#include "arm.c"
//#include "Start.c"

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

  motor(L_Front) = 0;
  motor(L_Rear) = 0;
  motor(R_Front) = 0;
  motor(R_Rear) = 0;
  nMotorEncoder[L_Rear]	= 0;
  nMotorEncoder[R_Rear]	= 0;


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
   //Start();

   ///////////////////////////////////////////////////////////
   ///////////////////////////////////////////////////////////
   ////                                                   ////
   ////    Add your robot specific autonomous code here.  ////
   ////                                                   ////
   ///////////////////////////////////////////////////////////
   ///////////////////////////////////////////////////////////




   Move(-78.0, 70.0);    // drive backward 78 inches
   wait10Msec(10);

   Turn_gyro(45.0);     // turn counterclockwise 45 degrees
   wait10Msec(10);

   Move(12.0, 70.0);    // drive forward 12 inches
   wait10Msec(10);

   Arm(205.0, 70.0);    // arm move 90 degrees
   wait10Msec(100);

   Move(14.0, 70.0);    // drive forward 14 inches
   wait10Msec(10);

   Arm(25.0, 70.0);    // arm move 90 degrees
   wait10Msec(100);

    Move(-4.0, 70.0);    // drive backward 4 inches
   wait10Msec(10);
}
