void Distkeep()
{
int DistFrom = 30; // in Cm
#include "drivers/lego-ultrasound.h"
int Deadband = 2;
int Distmin = 35;
// In Inches
float COUNTS_PER_INCH = 90.55;

nMotorEncoder[R_Motor] = 0;
nMotorEncoder[L_Motor] = 0;
servo[IRS_1] = 160;
servo[Block_Chuck] = 000;
ClearTimer(T1);
while (SensorValue[IR] != 6 && nMotorEncoder[ L_Motor] / COUNTS_PER_INCH < Distmin && nMotorEncoder[L_Motor] / COUNTS_PER_INCH < Distmin && time100[T1] < 50 )
{

	if ((USreadDist(SONAR_1) < DistFrom - Deadband) && (nMotorEncoder[ L_Motor] / COUNTS_PER_INCH > 18))
	{
		motor[L_Motor] = 25;
		motor[R_Motor] = 50;
  }
  else if ((USreadDist(SONAR_1) > DistFrom + Deadband) && (nMotorEncoder[ L_Motor] / COUNTS_PER_INCH > 18))
  {
  	motor[L_Motor] = 50;
  	motor[R_Motor] = 25;

  }
  else
  {
  	motor[L_Motor] = 50;
		motor[R_Motor] = 50;
	}
}

}
