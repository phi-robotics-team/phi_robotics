//=============================================================================
// Function: Move()
//
// Description:
//		This function will drive the robot the distance specified in "distance".
//
// Parameters: distance = distance in inches, Positive is forward,
//												Negative is backward
//=============================================================================
void Move( float distance, float max_speed )
{
	// Variables for move logic
	float const COUNTS_PER_INCH = 222.22;
	int const MAX_ENCODER_SPEED	 = 70;
	int countDistance;
	int direction = 1;
	int motorSpeed = 0;

	// Variables for turn adjusting
	int const MAX_GYRO_SPEED  = 85; //maximum motor speed allowed in turns
	int const MIN_GYRO_SPEED  = 40; //minimum motor speed allowed in turns
	int time;
	int time_old = 0;
	int delta_time;
	float maxVelocity = 180.0; // max angular velocity in deg/sec
	float GyroOld;
	float GyroNew;
	int rotDirection = 1;
	float degreesToGo;
	float DegreeGain = 5.0;
	float Angle;
	float Speed_Adjust = 0.0;


	nMotorPIDSpeedCtrl[B_L]= mtrSpeedReg;
	nMotorPIDSpeedCtrl[B_R]= mtrSpeedReg;
	nMotorPIDSpeedCtrl[F_L]= mtrSpeedReg;
	nMotorPIDSpeedCtrl[F_R]= mtrSpeedReg;
	nMaxRegulatedSpeed12V = 1000;

	// Initialize the turn adjusting variables
	Angle = 0.0;
	degreesToGo = 0.0;
	time_old = nPgmTime;
	GyroOld = 0.0;

	// Determine direction. Set to negative for backwards
	if( distance < 0 )
	{
		direction = -1;
	}
	// Calculate the distance to travel in encoder counts
	countDistance = abs(distance) * COUNTS_PER_INCH;

	// remove the backlash and freeplay from the motors before zeroing the encoders by commanding
	// a very low power for a short time

	// reset the motor encoders to zero
	nMotorEncoder[B_L] = 0;
	nMotorEncoder[B_R] = 0;
	nMotorEncoder[F_L] = 0;
	nMotorEncoder[F_R] = 0;

	motorSpeed = 5;
	motor[B_L] = direction * motorSpeed;
	motor[B_R] = direction * motorSpeed;
	motor[F_L] = direction * motorSpeed;
	motor[F_R] = direction * motorSpeed;
	wait1Msec(10);

	motorSpeed = MAX_ENCODER_SPEED;

	if ( (int)(abs(max_speed)) < MAX_ENCODER_SPEED)
	{
		motorSpeed = (int)max_speed;
	}

	motor[B_L] = direction * motorSpeed;
	motor[B_R] = direction * motorSpeed;
	motor[F_L] = direction * motorSpeed;
	motor[F_R] = direction * motorSpeed;

	while (abs(nMotorEncoder[F_R]) < countDistance && abs(nMotorEncoder[F_L])	 <	countDistance && abs(nMotorEncoder[B_L])<	 countDistance && abs(nMotorEncoder[B_R])<	countDistance) //while the encoder wheel turns one revolution
	{
		time =  nPgmTime; // this timer wraps around
		delta_time = abs(time - time_old); // delta time in ms

		if (delta_time < 1) // protect against divide by zero
		{
			delta_time = 1;
		}
		// read the gyro sensor minus the bias offset. GyroBias must be declared and
		// computed in the calling program.
		GyroNew = -((float)SensorValue[Gyro] - GyroBias);

		// limit the gyro to the max achievable by the bot to minimize data spikes.
		if (abs(GyroNew) > maxVelocity)
			GyroNew = sgn(GyroNew)*maxVelocity;

		// deadband for the gyro to eliminate drift due to noise
		if (abs(GyroNew) <= 0.5)
			GyroNew = 0.0;

		// compute the integral of the angular rate using a trapazoidal approximation
		// http://en.wikipedia.org/wiki/Numerical_integration
		Angle = Angle + 0.001 * (float)delta_time * 0.5 *(GyroNew + GyroOld);

		// update the old values for the next time through the loop
		time_old = time;
		GyroOld = GyroNew;

		// Calculate the rotation remaining
		if (abs(Angle) > 2)
		{
			// motor speed is proportional to the amount of rotation remaining
			Speed_Adjust = (int)(DegreeGain * Angle);
		}

		motor[B_L] = direction * motorSpeed - Speed_Adjust;
		motor[B_R] = direction * motorSpeed + Speed_Adjust;
		motor[F_L] = direction * motorSpeed - Speed_Adjust;
		motor[F_R] = direction * motorSpeed + Speed_Adjust;

		// This condition waits for motors D & E to come to an idle position. Both motors stop
		// and then jumps out of the loop
	}

	motor[B_L] = -direction*50;
	motor[B_R] = -direction*50;
	motor[F_L] = -direction*50;
	motor[F_R] = -direction*50;

	wait10Msec(1);

	motor[B_L] = 0;
	motor[B_R] = 0;
	motor[F_L] = 0;
	motor[F_R] = 0;

	// reset the back motor encoders to zero
	nMotorEncoder[F_L] = 0;
	nMotorEncoder[F_R] = 0;

} // End of Move()

//-----------------------------------------------------------------------------
//															End of file
//-----------------------------------------------------------------------------
