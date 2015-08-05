//=============================================================================
// Function: Move()
//
// Description:
//    This function will drive the robot the distance specified in "distance".
//
// Parameters: distance = distance in inches, Positive is forward,
//                        Negative is backward
//======
void lift_move( float inches )
{
	const int MAX_ENCODER_SPEED  = 100;
  const float MSECS_PER_inches = 378.75;
	float COUNTS_PER_inches = 378.75;
  int countDistance;
  int encoderCnt = 0;
  int encoderCnt2 = 0;
  int direction = 1;
  int motorSpeed = 0;
  int stoptime;
  float distcut = 0.75;
  int cut = 4;
  nMotorPIDSpeedCtrl[lift]= mtrSpeedReg;
	nMaxRegulatedSpeed12V = 1000;
	//string s;


nMotorPIDSpeedCtrl[lift] = mtrSpeedReg;
  // Determine direction. Set to negative for backwards
  if( inches < 0 )
  {
    direction = -1;
  }
  // Calculate the distance to travel in encoder counts
  countDistance = abs(inches) * COUNTS_PER_inches;

  // remove the backlash and freeplay from the motors before zeroing the encoders by commanding
  // a very low power for a short time

  motorSpeed = MAX_ENCODER_SPEED;
  motor[lift] = direction * motorSpeed;
  wait1Msec(10);

  nMotorEncoder[lift] = 0;
  ClearTimer(T1);

  motor[lift] = direction * motorSpeed;

   stoptime = abs(inches) * MSECS_PER_inches;

  while ((abs(nMotorEncoder[lift]) < countDistance)&& (time1[T1] < stoptime)) //while the encoder wheel turns one revolution
  {
    if (abs(nMotorEncoder[lift]) >= countDistance * distcut)
    {
    	motor[lift] = motorSpeed/cut;
    }

  }

//  motor[lift] = -direction*75;

  wait10Msec(20);

  motor[lift] = 0;


  // reset the back motor encoders to zero
  nMotorEncoder[lift] = 0;


} // End of Move()

//-----------------------------------------------------------------------------
//                              End of file
//-----------------------------------------------------------------------------
