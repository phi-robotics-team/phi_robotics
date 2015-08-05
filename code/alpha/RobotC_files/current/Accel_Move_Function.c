 //=============================================================================
// Function: Move()
//
// Description:
//    This function will drive the robot the distance specified in "distance".
//
// Parameters: distance = distance in inches, Positive is forward,
//                        Negative is backward
//=============================================================================
void Move( float distance)
{
	const float Conversion = 386.09/200;
	int X_axis;
  int Y_axis;
  int Z_axis;
  float time;
  float delta_time;
  float time_old;
  int accel_old;
  int accel_new;
  int accelBias = 0;
  int offset;
  float velocity_old;
  float velocity_new;
  float distance_driven;

  ClearTimer(T3);
  time_old = nPgmTime;
  accel_old = 0.0;
  velocity_old = 0;
  velocity_new = 0;
  distance_driven = 0;
  clearDebugStream();

  for (int i = 0; i < 20; i++)
	{
		HTACreadAllAxes(Accel, X_axis, Y_axis, Z_axis);

		accelBias += X_axis;
	}
	offset = accelBias/20;
	ClearTimer(T3);
  while(true)
  {
  		HTACreadAllAxes(Accel, X_axis, Y_axis, Z_axis);

  		int X_axis_new = X_axis - offset;

  		//time =  nPgmTime; // this timer wraps around

    	delta_time = time1[T3] * 0.001; // delta time in ms

    	accel_new = (X_axis_new) * Conversion;

    	velocity_new = velocity_old +(float)delta_time * 0.5 *(accel_new + accel_old);

			distance_driven += (float)delta_time * 0.5 *(velocity_new + velocity_old);

			writeDebugStream("%d\n", X_axis_new);


			ClearTimer(T3);
    time_old = time;
    accel_old = accel_new;
    velocity_old = velocity_new;

    if(abs(distance_driven) < abs(distance) * 0.20)
    {
    	motor[leftDrive] += sgn(distance) * 10;
    	motor[rightDrive] += sgn(distance) * 10;

    	if (abs(motor[leftDrive]) > 100 && abs(motor[rightDrive]) > 100)
    	{
    		motor[leftDrive] = sgn(distance) * 100;
    		motor[rightDrive] = sgn(distance) * 100;
    	}
  	}

  	else if (abs(distance_driven) > abs(distance) * 0.20 && distance_driven < abs(distance) * 0.80)
  	{
  		motor[leftDrive] = sgn(distance) * 100;
    	motor[rightDrive] = sgn(distance) * 100;
    }

   /* else if (abs(distance_driven) > abs(distance) * 0.80)
    {
    	motor[leftDrive] -= sgn(distance) * 10;
    	motor[rightDrive]-= sgn(distance) * 10;

    	if (abs(motor[leftDrive]) <= 10 || abs(motor[rightDrive]) <= 10)
    	{
    		motor[leftDrive] = sgn(distance) * 10;
    		motor[rightDrive] = sgn(distance) * 10;
    	}
    }*/

    else if (abs(distance_driven) >= abs(distance))
    {
    	motor[leftDrive] = 0;
    	motor[rightDrive] = 0;
    }
			wait10Msec(15);
 }
} // End of Move()

//-----------------------------------------------------------------------------
//                              End of file
//-----------------------------------------------------------------------------
