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
		nMotorPIDSpeedCtrl[leftDrive]= mtrSpeedReg;
		//nMotorPIDSpeedCtrl[rightDrive]= mtrSpeedReg;
	nMaxRegulatedSpeed12V = 1000;
  float COUNTS_PER_INCH = 18.482;
  int countDistance;
  int direction = 1;
  int motorSpeed = 0;
  int MAX_ENCODER_SPEED  = 50;
  int cut = 4;
	//float Sum_left;
	//float Sum_right;
	short Sum_left;
	short Sum_right;
	float RestofDst = 0.50;

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
  motor[leftDrive] = direction * motorSpeed;
  motor[rightDrive] = direction * motorSpeed;
  wait1Msec(10);

  if ( (int)(abs(max_speed)) < MAX_ENCODER_SPEED)
  	{
  		MAX_ENCODER_SPEED = (int)max_speed;
    }

  // reset the motor encoders to zero
  nMotorEncoder[leftDrive] = 0;
  nMotorEncoder[rightDrive] = 0;
//  nMotorEncoderTarget[F_L] = countDistance;
 // nMotorEncoderTarget[F_R] = countDistance;

  motorSpeed = MAX_ENCODER_SPEED;
  motor[leftDrive] = direction * motorSpeed;
  motor[rightDrive] = direction * motorSpeed;


  while (abs(nMotorEncoder[leftDrive]) < countDistance) //&& abs(nMotorEncoder[leftDrive])  <  countDistance)
  { //while the encoder value is less than the distance it needs to reach
  	clearDebugStream();

    wait10Msec(25);
    //Sum_left = abs(nMotorEncoder[leftDrive]); //Ads up the encodr values on the left and right to compare them
    //Sum_right = abs(nMotorEncoder[rightDrive]);
    Sum_left = nMotorEncoder[leftDrive]; //Ads up the encodr values on the left and right to compare them
    Sum_right = nMotorEncoder[rightDrive];
		writeDebugStream( "left: %d\n", nMotorEncoder[leftDrive] );
		writeDebugStream( "right: %d", nMotorEncoder[rightDrive] );


    /*if (Sum_left > Sum_right)
    {
    	motor[F_R] = direction * MAX_ENCODER_SPEED + 5;
    	motor[B_R] = direction * MAX_ENCODER_SPEED + 5;
    }
    	else if (Sum_left < Sum_right)
    	{
    		motor[F_L] = direction * MAX_ENCODER_SPEED + 5;
    		motor[B_L] = direction * MAX_ENCODER_SPEED + 5;
      }*/
    if (abs(nMotorEncoder[leftDrive]) >= countDistance * RestofDst )// || abs(nMotorEncoder[leftDrive]) >=  countDistance * RestofDst)
    { //If the encoder values becomes greater than a certain percentage of the total value needed to reach the desired distance.
    		//motorSpeed = motorSpeed/cut;
        motor[leftDrive]  = direction * motorSpeed; //the motor value will continue to be cut until the distance is reached.
        motor[rightDrive] = direction * motorSpeed;
    }


   }

  motor[leftDrive] = -direction*20;
  motor[rightDrive] = -direction*20;

  wait10Msec(10);

  motor[leftDrive] = 0;
  motor[rightDrive] = 0;

  // reset the back motor encoders to zero
  nMotorEncoder[leftDrive] = 0;
  nMotorEncoder[rightDrive] = 0;

} // End of Move()

//-----------------------------------------------------------------------------
//                              End of file
//-----------------------------------------------------------------------------
