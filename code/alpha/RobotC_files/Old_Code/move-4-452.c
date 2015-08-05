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
	float Sum_left;
	float Sum_right;
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

  ClearTimer(T1);

	while (abs(nMotorEncoder[R_Motor]) < countDistance || abs(nMotorEncoder[L_Motor])  <  countDistance && time100[T1] < 1.3 * distance)
	{ //while the encoder value is less than the distance it needs to reach
		wait10Msec(25);
		Sum_left = abs(nMotorEncoder[L_Motor]); //Ads up the encodr values on the left and right to compare them
		Sum_right = abs(nMotorEncoder[R_Motor]);



		if (abs(nMotorEncoder[R_Motor]) >= countDistance * RestofDst  || abs(nMotorEncoder[L_Motor]) >=  countDistance * RestofDst)
		{ //If the encoder values becomes greater than a certain percentage of the total value needed to reach the desired distance.
			motor[L_Motor] = MAX_ENCODER_SPEED/cut; //the motor value will continue to be cut until the distance is reached.
			motor[R_Motor] = MAX_ENCODER_SPEED/cut;
		}


	}

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
