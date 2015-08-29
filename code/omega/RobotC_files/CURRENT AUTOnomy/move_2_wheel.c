void Move( float distance, float max_speed )
{
	int direction = 1;
	int motorSpeed = 0;
	nMaxRegulatedSpeed12V = 1000;
	float COUNTS_PER_INCH = 57.05;//slightly off. need recalibration
	int MAX_ENCODER_SPEED  = 50;
	int cut = 3;
	float Sum_left;
	float Sum_right;
	float RestofDst = 0.75;

	moveRunning = 1;

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
	countDistance = abs(distance)* COUNTS_PER_INCH;

	// remove the backlash and freeplay from the motors before zeroing the encoders by commanding
	// a very low power for a short time

	motorSpeed = 5;
	motor[B_L] = direction * motorSpeed;
	motor[B_R] = direction * motorSpeed;
	wait1Msec(10);

	if ( (int)(abs(max_speed)) < MAX_ENCODER_SPEED)
	{
		MAX_ENCODER_SPEED = (int)max_speed;
	}

	// reset the motor encoders to zero
	nMotorEncoder[B_L] = 0;
	nMotorEncoder[B_R] = 0;

	motor[B_L] = direction * MAX_ENCODER_SPEED;
	motor[B_R] = direction * MAX_ENCODER_SPEED;

	while (abs(nMotorEncoder[B_L])<  countDistance && abs(nMotorEncoder[B_R])<  countDistance)
	{ //while the encoder value is less than the distance it needs to reach
		wait10Msec(25);
		if (abs(nMotorEncoder[B_L]) >= countDistance * RestofDst && abs(nMotorEncoder[B_R]) >=  countDistance * RestofDst)
		{ //If the encoder values becomes greater than a certain percentage of the total value needed to reach the desired distance.
			motor[B_L] = MAX_ENCODER_SPEED/cut; //the motor value will continue to be cut until the distance is reached.
			motor[B_R] = MAX_ENCODER_SPEED/cut;
		}
	}

	motor[B_L] = 0;
	motor[B_R] = 0;

	// reset the back motor encoders to zero
	nMotorEncoder[B_L] = 0;
	nMotorEncoder[B_R] = 0;
	moveRunning = 0;

} // End of Move()