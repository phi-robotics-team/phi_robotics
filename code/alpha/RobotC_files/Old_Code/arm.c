//=============================================================================
// Function: Move()
//
// Description:
//    This function will drive the robot the distance specified in "distance".
//
// Parameters: distance = distance in inches, Positive is forward,
//                        Negative is backward
//======
void Arm_move( float Degrees )
{
	int state = 3;
  float COUNTS_PER_Degree = 1;
  int countDistance;
  int direction = 1;
  int motorSpeed = 0;
  int MAX_ENCODER_SPEED  = 25;
  int max_speed = 25;
  nMotorPIDSpeedCtrl[Arm]= mtrSpeedReg;
	nMaxRegulatedSpeed12V = 1000;


nMotorPIDSpeedCtrl[Arm] = mtrSpeedReg;
  // Determine direction. Set to negative for backwards
  if( Degrees < 0 )
  {
    direction = -1;
  }
  // Calculate the distance to travel in encoder counts
  countDistance = abs(Degrees) * COUNTS_PER_Degree;

  // remove the backlash and freeplay from the motors before zeroing the encoders by commanding
  // a very low power for a short time

  motorSpeed = 5;
  motor[Arm] = direction * motorSpeed;
  wait1Msec(10);

  if ( (int)(abs(max_speed)) < MAX_ENCODER_SPEED) {
    MAX_ENCODER_SPEED = (int)max_speed;
  }

  // reset the motor encoders to zero
  nMotorEncoder[Arm] = 0;

//  nMotorEncoderTarget[F_L] = countDistance;
 // nMotorEncoderTarget[F_R] = countDistance;

  motor[Arm] = direction * MAX_ENCODER_SPEED;



  while (abs(nMotorEncoder[Arm]) < countDistance) //while the encoder wheel turns one revolution
  {
    // This condition waits for motors D & E to come to an idle position. Both motors stop
    // and then jumps out of the loop
  }

  motor[Arm] = -direction*75;

  wait10Msec(20);

  motor[Arm] = 0;


  // reset the back motor encoders to zero
  nMotorEncoder[Arm] = 0;


} // End of Move()

//-----------------------------------------------------------------------------
//                              End of file
//-----------------------------------------------------------------------------
