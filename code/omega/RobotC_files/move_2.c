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
  float COUNTS_PER_INCH = 107;
  int countDistance;
  int direction = 1;
  int motorSpeed = 0;
  int MAX_ENCODER_SPEED  = 70;
 /* float encoderL_Rear = nMotorEncoder[L_Rear];
  float encoderR_Rear = nMotorEncoder[R_Rear];
  float encoderL_Front = nMotorEncoder[L_Front];
  float encoderR_Front = nMotorEncoder[R_Front];*/

  // Determine direction. Set to negative for backwards
  if( distance > 0 )
  {
    direction = -1;
  }
  // Calculate the distance to travel in encoder counts
  countDistance = abs(distance) * COUNTS_PER_INCH;

  // remove the backlash and freeplay from the motors before zeroing the encoders by commanding
  // a very low power for a short time

  motorSpeed = 5;
  motor[L_Rear] = direction * motorSpeed;
  motor[R_Rear] = direction * motorSpeed;
  motor[L_Front] = direction * motorSpeed;
  motor[R_Front] = direction * motorSpeed;
  wait1Msec(10);

  if ( (int)(abs(max_speed)) < MAX_ENCODER_SPEED) {
    MAX_ENCODER_SPEED = (int)max_speed;
  }

  // reset the motor encoders to zero
  nMotorEncoder[L_Front] = 0;
  nMotorEncoder[R_Front] = 0;

//  nMotorEncoderTarget[F_L] = countDistance;
 // nMotorEncoderTarget[F_R] = countDistance;

time10[1]=0;

while (abs(nMotorEncoder[L_Front]) < countDistance && abs(nMotorEncoder[R_Front])  <  countDistance) //while the encoder wheel turns one revolution
// while (time10[1] <300)
{
  motor[L_Rear] = direction * MAX_ENCODER_SPEED;
  motor[R_Rear] = direction * MAX_ENCODER_SPEED;
  motor[L_Front] = direction * MAX_ENCODER_SPEED;
  motor[R_Front] = direction * MAX_ENCODER_SPEED;

  }

  //motor[L_Rear] = -direction*50;
  //motor[R_Rear] = -direction*50;
  //motor[L_Front] = -direction*50;
  //motor[R_Front] = -direction*50;

  wait10Msec(1);

  motor[L_Rear] = 0;
  motor[R_Rear] = 0;
  motor[L_Front] = 0;
  motor[R_Front] = 0;

 // nxtDisplayBigTextLine(2, "%6d", nMotorEncoder[L_Front]);
 // nxtDisplayBigTextLine(4, "%6d", nMotorEncoder[R_Front]);

  // reset the back motor encoders to zero

nMotorEncoder[L_Front] = 0;
nMotorEncoder[R_Front] = 0;

} // End of Move()

//-----------------------------------------------------------------------------
//                              End of file
//-----------------------------------------------------------------------------
