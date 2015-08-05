#include "drivers/hitechnic-sensormux.h"
#include "drivers/hitechnic-accelerometer.h"

const tMUXSensor ACCEL = msensor_S4_3;

//=============================================================================
// Function: Move()
//
// Description:
//    This function will drive the robot the distance specified in "distance".
//
// Parameters: distance = distance in inches, Positive is forward,
//                        Negative is backward
//=============================================================================
void Move( float distance, float max_speed )
{
	nMotorPIDSpeedCtrl[L_Motor]= mtrSpeedReg;
	nMotorPIDSpeedCtrl[R_Motor]= mtrSpeedReg;
	nMaxRegulatedSpeed12V = 1000;
	float COUNTS_PER_INCH = 90.55;
	int countDistance;
	int direction = 1;
	int motorSpeed = 0;
	int MAX_ENCODER_SPEED  = 50;
	int cut = 3;
	short x_axis = 0;
	short y_axis = 0;
	short z_axis = 0;
	short x_axis_old = 0;
	short y_axis_old = 0;
	short z_axis_old = 0;
	int deadband = 10;
	float RestofDst = 0.75;

	// Determine direction. Set to negative for backwards
	if( distance < 0 )
	{
		direction = -1;
	}
	if( distance <= 5 )
	{
		motorSpeed = MAX_ENCODER_SPEED/cut;
	}
	// Calculate the distance to travel in encoder counts
	countDistance = abs(distance) * COUNTS_PER_INCH;

	// remove the backlash and freeplay from the motors before zeroing the encoders by commanding
	// a very low power for a short time

	motorSpeed = 5;
	motor[L_Motor] = direction * motorSpeed;
	motor[R_Motor] = direction * motorSpeed;
	wait1Msec(10);

	if ( (int)(abs(max_speed)) < MAX_ENCODER_SPEED)
	{
		MAX_ENCODER_SPEED = (int)max_speed;
	}

	// reset the motor encoders to zero
	nMotorEncoder[L_Motor] = 0;
	nMotorEncoder[R_Motor] = 0;
	//  nMotorEncoderTarget[F_L] = countDistance;
	// nMotorEncoderTarget[F_R] = countDistance;

	motor[L_Motor] = direction * MAX_ENCODER_SPEED;
	motor[R_Motor] = direction * MAX_ENCODER_SPEED;

	HTACreadAllAxes(ACCEL, x_axis_old, y_axis_old, z_axis_old);

	while (abs(nMotorEncoder[R_Motor]) < countDistance || abs(nMotorEncoder[L_Motor])  <  countDistance)
	{
		HTACreadAllAxes(ACCEL, x_axis, y_axis, z_axis);

		if (x_axis > x_axis_old + deadband)
		{
			motor[L_Motor] = motor[L_Motor]/2;
	  	HTACreadAllAxes(ACCEL, x_axis_old, y_axis_old, z_axis_old);
		}

	  else if (x_axis < x_axis_old - deadband)
		{
			motor[R_Motor] = motor[R_Motor]/2;
	    HTACreadAllAxes(ACCEL, x_axis_old, y_axis_old, z_axis_old);
		}
		wait10Msec(10);

		if (abs(nMotorEncoder[R_Motor]) >= countDistance * RestofDst  || abs(nMotorEncoder[L_Motor]) >=  countDistance * RestofDst)
		{ //If the encoder values becomes greater than a certain percentage of the total value needed to reach the desired distance.
			motor[L_Motor] = MAX_ENCODER_SPEED/cut; //the motor value will continue to be cut until the distance is reached.
			motor[R_Motor] = MAX_ENCODER_SPEED/cut;
		}
		nxtDisplayCenteredTextLine( 8, "Left %d Right %d", nMotorEncoder[L_Motor], nMotorEncoder[R_Motor]);

	}//end of while

	motor[L_Motor] = -direction*20;
	motor[R_Motor] = -direction*20;

	wait10Msec(10);

	motor[L_Motor] = 0;
	motor[R_Motor] = 0;

	// reset the back motor encoders to zero
	nMotorEncoder[L_Motor] = 0;
	nMotorEncoder[R_Motor] = 0;

} // End of Move()

//-----------------------------------------------------------------------------
//                              End of file
//-----------------------------------------------------------------------------
