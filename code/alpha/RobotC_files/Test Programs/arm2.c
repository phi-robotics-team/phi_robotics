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
	const int MAX_ENCODER_SPEED  = 25;
  const float MSECS_PER_DEGREE = 25;
	float COUNTS_PER_Degree = 25;
  int countDistance;
  int encoderCnt = 0;
  int encoderCnt2 = 0;
  int direction = 1;
  int motorSpeed = 0;
  int stoptime;
  float distcut = 0.75;
  int cut = 4;
  nMotorPIDSpeedCtrl[Arm]= mtrSpeedReg;
	nMaxRegulatedSpeed12V = 1000;
	string s;


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

  motorSpeed = MAX_ENCODER_SPEED;
  motor[Arm] = direction * motorSpeed;
  wait1Msec(10);

  nMotorEncoder[Arm] = 0;
  ClearTimer(T1);

  motor[Arm] = direction * motorSpeed;

   stoptime = abs(Degrees) * MSECS_PER_DEGREE;

  while ((abs(nMotorEncoder[Arm]) < countDistance)&& (time1[T1] < stoptime)) //while the encoder wheel turns one revolution
  {
    if (abs(nMotorEncoder[Arm]) >= countDistance * distcut)
    {
    	motor[Arm] = motorSpeed/cut;
    }

  }

//  motor[Arm] = -direction*75;

  wait10Msec(20);

  motor[Arm] = 0;


  // reset the back motor encoders to zero
  nMotorEncoder[Arm] = 0;


} // End of Move()

//-----------------------------------------------------------------------------
//                              End of file
//-----------------------------------------------------------------------------
