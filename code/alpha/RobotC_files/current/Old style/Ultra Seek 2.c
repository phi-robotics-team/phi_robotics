//=============================================================================
// Function: Move()
//
// Description:
//    This function will drive the robot the distance specified in "distance".
//
// Parameters: distance = distance in inches, Positive is forward,
//                        Negative is backward
//======


void Ultra_Seek( int Min, int Max )
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

  Angle = 0.0;
	degreesToGo = 0.0;
	time_old = nPgmTime;
	GyroOld = 0.0;
	wait1Msec(100);

	while(SensorValue[SONAR_1] > Min)
		{
			while (SensorValue[SONAR_1] > Min && SensorValue[SONAR_1] < Max)
			{
				motor[rightDrive] = 20;
				motor[leftDrive] = 20;
			}
				motor[rightDrive] = 0;
				motor[leftDrive] = 0;
				wait10Msec(55);

				time100[T1] = 0;

				time100[T2] = 0;

			while(SensorValue[SONAR_1] > Max)
			{

				if(time100[T1] < 30)
				{
				 motor[rightDrive] = 20;
				 motor[leftDrive] = -20;
		  	}


		  	if(time100[T2] > 30)
				{
				 motor[rightDrive] = -20;
				 motor[leftDrive] = 20;
		  	}

			}
			ClearTimer(T3);

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
		}
} // End of Move()

//-----------------------------------------------------------------------------
//                              End of file
//-----------------------------------------------------------------------------
