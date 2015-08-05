//=============================================================================
// Function: Move()
//
// Description:
//    This function will turn the arm the degrees specified in "degrees".
//
// Parameters: degrees = degrees to rotate arm, Positive is forward,
//                        Negative is backward
//=============================================================================
void Arm( float degrees, float max_speed )
{
  float COUNTS_PER_INCH = 2.05;
  int countDistance;
  int direction = 1;
  int motorSpeed = 0;
  int MAX_ENCODER_SPEED  = 70;
  nMotorPIDSpeedCtrl[Arm_motor] = mtrSpeedReg;
	nMaxRegulatedSpeed12V = 1000;
	float encoderArm = nMotorEncoder[Arm_motor];

  // Determine direction. Set to negative for backwards
  if( degrees > 0 )
  {
    direction = -1;
  }
  // Calculate the degrees to travel in encoder counts
  countDistance = abs(degrees) * COUNTS_PER_INCH;

  // remove the backlash and freeplay from the motors before zeroing the encoders by commanding
  // a very low power for a short time

  motorSpeed = 5;
  motor[Arm_motor] = direction * motorSpeed;

  wait1Msec(10);

  if ( (int)(abs(max_speed)) < MAX_ENCODER_SPEED) {
    MAX_ENCODER_SPEED = (int)max_speed;
  }

  // reset the motor encoders to zero
  nMotorEncoder[Arm_motor] = 0;

  motor[Arm_motor] = direction * MAX_ENCODER_SPEED;

  while (abs(nMotorEncoder[Arm_motor]) < countDistance) //while the encoder wheel turns one revolution
  {
    // This condition waits for motors D & E to come to an idle position. Both motors stop
    // and then jumps out of the loop
  	encoderArm = nMotorEncoder[Arm_motor];

		wait10Msec(50); // give the Messagecount time to change it changes every 50ms

		if(encoderArm == nMotorEncoder[Arm_motor]) // checks to see if the Message change if has not it is Disconnected
		{
			motor[Arm_motor] = 0;
		}
  }

  //motor[Arm_motor] = -direction*50;

  wait10Msec(1);

  motor[Arm_motor] = 0;

  // reset the back motor encoders to zero
  nMotorEncoder[Arm_motor] = 0;

} // End of Move()

//-----------------------------------------------------------------------------
//                              End of file
//-----------------------------------------------------------------------------
