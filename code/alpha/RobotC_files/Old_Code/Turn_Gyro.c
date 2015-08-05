 //=============================================================================
// Function: turn_gyro()
//
// Description:
//    This function will turn the robot counter clock-wise (CCW) in place by
//    the number of degrees specified in "turnDegrees". This function uses the gyro and
//    integrates to determine the angle
//
// Parameters: turnDegrees = degrees to rotate, Positive is CCW,
//                           Negative is CW
//=============================================================================
void Turn( float turnDegrees )
{
	int state = 2;
  int time;
  int time_old = 0;
  int delta_time;
  float maxVelocity = 180.0; // max angular velocity in deg/sec
  float GyroOld;
  float GyroNew;
  int rotDirection = 1;
  int motorSpeed = 0;
  float DegreeGain = 5.0;
  float degreesToGo;
  int MAX_GYRO_SPEED  = 85; //maximum motor speed allowed in turns
  int MIN_GYRO_SPEED  = 40; //minimum motor speed allowed in turns
  float Angle;

  // Determine the rotation direction. Set to negative for clock-wise rotation.
  if( turnDegrees < 0 ) rotDirection = -1;

  // Set the Angle and components to zero befor turning
  Angle = 0.0;
  degreesToGo = 0.0;
  time_old = nPgmTime;
  GyroOld = 0.0;
  wait1Msec(100);

  // remove the backlash and freeplay from the motors before zeroing the encoders by commanding
  // a very low power for a short time

  motorSpeed = 5;
  motor[L_Motor] = -rotDirection * motorSpeed;
  motor[R_Motor] = rotDirection * motorSpeed;
  wait1Msec(10);

  // reset the back motor encoders to zero
  nMotorEncoder[R_Motor] = 0;
  nMotorEncoder[L_Motor] = 0;

  ClearTimer(T3);
  //---------------------------------------------------------------------------
  // Move the motors until the gyro Angle indicates the rotation is complete
  //---------------------------------------------------------------------------
  while( ( abs(turnDegrees) - abs(Angle) ) > 3 )
  {
    time =  nPgmTime; // this timer wraps around
    delta_time = abs(time - time_old); // delta time in ms

    if (delta_time < 1) // protect against divide by zero
    {
      delta_time = 1;
    }
    // read the gyro sensor minus the bias offset. GyroBias must be declared and
    // computed in the calling program.
    GyroNew = -((float)SensorValue[Gyro] - GyroBias);

    // limit the gyro to the max achievable by the bot to minimize data spikes.
    if (abs(GyroNew) > maxVelocity) GyroNew = sgn(GyroNew)*maxVelocity;

    // deadband for the gyro to eliminate drift due to noise
    if (abs(GyroNew) <= 0.2) GyroNew = 0.0;

    // compute the integral of the angular rate using a trapazoidal approximation
    // http://en.wikipedia.org/wiki/Numerical_integration
    Angle = Angle + 0.001 * (float)delta_time * 0.5 *(GyroNew + GyroOld);

    // update the old values for the next time through the loop
    time_old = time;
    GyroOld = GyroNew;

    // Calculate the rotation remaining
    degreesToGo =  abs(turnDegrees) - abs(Angle);

    // motor speed is proportional to the amount of rotation remaining
    motorSpeed = (int)(DegreeGain * abs(degreesToGo));

    // limit the motor speed to be greater than 15 and less than 75
    if (abs(motorSpeed) > MAX_GYRO_SPEED) motorSpeed = MAX_GYRO_SPEED;
    if (abs(motorSpeed) < MIN_GYRO_SPEED) motorSpeed = MIN_GYRO_SPEED;

    motor[L_Motor] = rotDirection * motorSpeed ; // looking from the top, left side moves back, right
    motor[R_Motor] = -rotDirection * motorSpeed ; // side moves forward for (+) CCW rotation

    if( time100[T3] > 50 ) break; // if the bot is not done turning in 5 sec, quit
    wait1Msec(15); // wait 20 ms to allow a reasonable period for the integration

  } // End while rotation remaining

  // since we have now reached the target rotation (the while loop is done), stop all drive motors

  motor[R_Motor] = 0;
  motor[L_Motor] = 0;

  // reset the back motor encoders to zero
  nMotorEncoder[R_Motor] = 0;
  nMotorEncoder[L_Motor] = 0;

} // End of Turn_Gyro()

//-----------------------------------------------------------------------------
//                              End of file
//-----------------------------------------------------------------------------
