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
		}
} // End of Move()

//-----------------------------------------------------------------------------
//                              End of file
//-----------------------------------------------------------------------------
