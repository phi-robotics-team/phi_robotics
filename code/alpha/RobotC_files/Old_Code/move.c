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
		nMotorPIDSpeedCtrl[B_L]= mtrSpeedReg;
		nMotorPIDSpeedCtrl[B_R]= mtrSpeedReg;
		nMotorPIDSpeedCtrl[F_L]= mtrSpeedReg;
		nMotorPIDSpeedCtrl[F_R]= mtrSpeedReg;
		int state = 1;
	nMaxRegulatedSpeed12V = 1000;
  float COUNTS_PER_INCH = 222.22;
  int countDistance;
  int direction = 1;
  int motorSpeed = 0;
  int MAX_ENCODER_SPEED  = 70;
	float Sum_left;
	float Sum_right;

  // Determine direction. Set to negative for backwards
  if( distance < 0 )
  {
    direction = -1;
  }
  // Calculate the distance to travel in encoder counts
  countDistance = abs(distance) * COUNTS_PER_INCH;

  // remove the backlash and freeplay from the motors before zeroing the encoders by commanding
  // a very low power for a short time

  motorSpeed = 5;
  motor[B_L] = direction * motorSpeed;
  motor[B_R] = direction * motorSpeed;
  motor[F_L] = direction * motorSpeed;
  motor[F_R] = direction * motorSpeed;
  wait1Msec(10);

  if ( (int)(abs(max_speed)) < MAX_ENCODER_SPEED) {
    MAX_ENCODER_SPEED = (int)max_speed;
  }

  // reset the motor encoders to zero
  nMotorEncoder[F_L] = 0;
  nMotorEncoder[F_R] = 0;

//  nMotorEncoderTarget[F_L] = countDistance;
 // nMotorEncoderTarget[F_R] = countDistance;

  motor[B_L] = direction * MAX_ENCODER_SPEED;
  motor[B_R] = direction * MAX_ENCODER_SPEED;
  motor[F_L] = direction * MAX_ENCODER_SPEED;
  motor[F_R] = direction * MAX_ENCODER_SPEED;


  while (abs(nMotorEncoder[F_R]) < countDistance && abs(nMotorEncoder[F_L])  <  countDistance && abs(nMotorEncoder[B_L])<  countDistance && abs(nMotorEncoder[B_R])<  countDistance) //while the encoder wheel turns one revolution
  {
    wait10Msec(25);
    Sum_left = (abs(nMotorEncoder[F_L]) + abs(nMotorEncoder[B_L]));
    Sum_right = (abs(nMotorEncoder[F_R]) + abs(nMotorEncoder[B_R]));

    if (Sum_left > Sum_right)
    {
    	motor[F_R] = direction * MAX_ENCODER_SPEED + 30;
    	motor[B_R] = direction * MAX_ENCODER_SPEED + 30;
  }
    	else if (Sum_left < Sum_right)
    	{
    		motor[F_L] = direction * MAX_ENCODER_SPEED + 30;
    		motor[B_L] = direction * MAX_ENCODER_SPEED + 30;
  }

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
//                              End of file
//-----------------------------------------------------------------------------
