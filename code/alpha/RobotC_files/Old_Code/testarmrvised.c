#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Sensor, S2,     IR,             sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S3,     Gyro,           sensorI2CHiTechnicGyro)
#pragma config(Sensor, S4,     accel,          sensorI2CHiTechnicAccel)
#pragma config(Motor,  motorA,          Bly,           tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     Jack,          tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     Ramp,          tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     F_L,           tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     B_L,           tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     Arm,           tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     Lift,          tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     F_R,           tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C4_2,     B_R,           tmotorTetrix, PIDControl, reversed, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// ***********  Globals *********

float const COUNTS_PER_INCH  = 109.0;
float GyroBias = 2.0;

#include "arm2.c"

task main()
{

  int nDelay = 300;

  bFloatDuringInactiveMotorPWM = false;

  motor(F_L) = 0;
  motor(F_R) = 0;
  motor(B_L) = 0;
  motor(B_R) = 0;
  nMotorEncoder[F_L]	= 0;
  nMotorEncoder[F_R]	= 0;
  nMotorEncoder[B_L] = 0;
  nMotorEncoder[B_R] = 0;



    Arm_move(90.0);    // drive forward 48 inches

    PlaySound(soundBeepBeep);
    wait10Msec(nDelay);


} // End of main()

//-----------------------------------------------------------------------------
//                              End of file
//-----------------------------------------------------------------------------