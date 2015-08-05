     //========================================================================
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
  float COUNTS_PER_INCH = 100;
  int countDistance;
  int direction = 1;
  int motorSpeed = 0;
  int MAX_ENCODER_SPEED  = 70;
 // float encoderL_Rear = nMotorEncoder[L_Rear];
//  float encoderR_Rear = nMotorEncoder[R_Rear];
 // float encoderL_Front = nMotorEncoder[L_Front];
//  float encoderR_Front = nMotorEncoder[R_Front];

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
  //motor[L_Rear] = direction * motorSpeed;
  //motor[R_Rear] = direction * motorSpeed;
  //motor[Left_Side] = direction * motorSpeed;
//  motor[Right_Side] = direction * motorSpeed;
  wait1Msec(10);

  if ( (int)(abs(max_speed)) < MAX_ENCODER_SPEED) {
    MAX_ENCODER_SPEED = (int)max_speed;
  }

  // reset the motor encoders to zero
 // nMotorEncoder[L_Rear] = 0;
 // nMotorEncoder[R_Rear] = 0;

//  nMotorEncoderTarget[F_L] = countDistance;
 // nMotorEncoderTarget[F_R] = countDistance;

//  motor[L_Rear] = direction * MAX_ENCODER_SPEED;
 // motor[R_Rear] = direction * MAX_ENCODER_SPEED;
//  motor[L_Front] = direction * MAX_ENCODER_SPEED;
 // motor[R_Front] = direction * MAX_ENCODER_SPEED;


	//while (abs(nMotorEncoder[L_Rear]) < countDistance && abs(nMotorEncoder[R_Rear])  <  countDistance) //while the encoder wheel turns one revolution
  {
    // This condition waits for motors D & E to come to an idle position. Both motors stop
    // and then jumps out of the loop

 		//encoderL_Rear = nMotorEncoder[L_Rear];
  	//encoderR_Rear = nMotorEncoder[R_Rear];
 		//coderL_Front = nMotorEncoder[L_Front];
 		//coderR_Front = nMotorEncoder[R_Front];

		wait10Msec(25); // give the Messagecount time to change it changes every 50ms

	//f(encoderL_Rear == nMotorEncoder[L_Rear] && encoderR_Rear == nMotorEncoder[R_Rear] && encoderL_Front == nMotorEncoder[L_Front] && encoderR_Front == nMotorEncoder[R_Front]) // checks to see if the Message change if has not it is Disconnected
		{
			//tor[L_Rear] = 0;
	 	//otor[R_Rear] = 0;
		//otor[Left_Side] = 0;
		//otor[Right_Side] = 0;
		}
  }

 //otor[L_Rear] = -direction*50;
  //tor[R_Rear] = -direction*50;
 //otor[Left_Side -direction*50;
 //otor[Right_Side -direction*50;

  wait10Msec(1);

 //otor[L_Rear] = 0;
 //otor[R_Rear] = 0;
 //otor[Left_Side= 0;
  //tor[Right_Side 0;

  // reset the back motor encoders to zero
 //MotorEncoder[L_Rear] = 0;
 //MotorEncoder[R_Rear] = 0;

} // End of Move()

//-----------------------------------------------------------------------------
//                              End of file
//-----------------------------------------------------------------------------
