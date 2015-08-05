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
		nMotorPIDSpeedCtrl[R_Rear]= mtrSpeedReg;
		nMotorPIDSpeedCtrl[L_Rear]= mtrSpeedReg;
	//	nMotorPIDSpeedCtrl[F_L]= mtrSpeedReg;
	//	nMotorPIDSpeedCtrl[F_R]= mtrSpeedReg;
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
  motor[Front_left] = direction * motorSpeed;
  motor[R_Rear] = direction * motorSpeed;
  motor[L_Front] = direction * motorSpeed;
  motor[R_Front] = direction * motorSpeed;
  wait1Msec(10);

  if ( (int)(abs(max_speed)) < MAX_ENCODER_SPEED) {
    MAX_ENCODER_SPEED = (int)max_speed;
  }

  // reset the motor encoders to zero
  nMotorEncoder[L_Rear] = 0;
  nMotorEncoder[R_Rear] = 0;

//  nMotorEncoderTarget[F_L] = countDistance;
 // nMotorEncoderTarget[F_R] = countDistance;

  motor[L_Rear] = direction * MAX_ENCODER_SPEED;
  motor[R_Rear] = direction * MAX_ENCODER_SPEED;
  motor[L_Front] = direction * MAX_ENCODER_SPEED;
  motor[R_Front] = direction * MAX_ENCODER_SPEED;


  while (abs(nMotorEncoder[L_Rear])<  countDistance && abs(nMotorEncoder[R_Rear])<  countDistance) //while the encoder wheel turns one revolution
  {
    wait10Msec(25);
    Sum_left = (abs(nMotorEncoder[L_Rear]));
    Sum_right = (abs(nMotorEncoder[R_Rear]));

    if (Sum_left > Sum_right)
    {
      motor[R_Front] = direction * MAX_ENCODER_SPEED + 30;
    	motor[R_Rear] = direction * MAX_ENCODER_SPEED + 30;
  }
    	else if (Sum_left < Sum_right)
    	{
    		motor[L_Front] = direction * MAX_ENCODER_SPEED + 30;
    		motor[L_Rear] = direction * MAX_ENCODER_SPEED + 30;
  }

    }

  motor[L_Rear] = -direction*50;
  motor[R_Rear] = -direction*50;
  //motor[F_L] = -direction*50;
 // motor[F_R] = -direction*50;

  wait10Msec(1);

  motor[L_Rear] = 0;
  motor[R_Rear] = 0;
 // motor[F_L] = 0;
 //motor[F_R] = 0;

  // reset the back motor encoders to zero
 // nMotorEncoder[F_L] = 0;
 //// nMotorEncoder[F_R] = 0;

} // End of Move()

//-----------------------------------------------------------------------------
//                              End of file
//-----------------------------------------------------------------------------
