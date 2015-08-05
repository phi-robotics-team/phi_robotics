#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     Gyro,           sensorI2CHiTechnicGyro)
#pragma config(Sensor, S3,     mux,            sensorI2CCustom)
#pragma config(Sensor, S4,     htspb,          sensorI2CCustom)
#pragma config(Motor,  mtr_S1_C1_1,     leftFront,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     leftRear,      tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     intake,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     rightRear,     tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     rightFront,    tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_2,     lift,          tmotorTetrix, openLoop, encoder)
#pragma config(Servo,  srvo_S1_C4_1,    inputstop,            tServoStandard)
#pragma config(Servo,  srvo_S1_C4_2,    hook1,                tServoStandard)
#pragma config(Servo,  srvo_S1_C4_3,    hook2,                tServoStandard)
#pragma config(Servo,  srvo_S1_C4_4,    irTurret,             tServoStandard)
#pragma config(Servo,  srvo_S1_C4_5,    ultraTurret,          tServoStandard)
#pragma config(Servo,  srvo_S1_C4_6,    output,               tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#define ir msensor_S3_1
#define touch msensor_S3_2
#define accel msensor_S3_3
#define ultraSonic msensor_S3_4
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "hitechnic-superpro.h"

task main()
{
	//start robot
	float dist = 32.5;
	int clockPin = 0x1; //Pin 0
	int sigAPin = 0x02; //Pin 1
	int sigBPin = 0x04; //Pin 2
	/*ubyte mask = 0b11111111;
	while(true){
		clearDebugStream();
	HTSPBsetupIO(htspb, 0x00);
	writeDebugStreamLine("%d", HTSPBreadIO(htspb, mask));
	wait10Msec(10);}*/
	ubyte mask = 0;

	mask = clockPin | sigAPin;
	HTSPBsetupIO(htspb, mask);
	mask = 0x00;
	HTSPBwriteIO(htspb, mask);

	mask = sigBPin;
	while (HTSPBreadIO(htspb, mask) == sigBPin);

	int base = abs(dist);
	int dir = sgn(dist);
	int dec = (dist - (float)base) * 100;
	for (int i = 0; i < 5; i++)
	{
		mask = clockPin;
		HTSPBsetupIO(htspb, mask);
		mask = 0x00;
		HTSPBwriteIO(htspb, mask);

		if (i < 4)
		{
			if ((base & (1 << (7 - (2 * i)))) > 0)
				mask |= sigAPin;
			if ((base & (1 << (6 - (2 * i)))) > 0)
				mask |= sigBPin;
		}
		else if (i > 3 && i < 7)
		{
			if ((dec & (1 << (5 - (2 * (i - 4))))) > 0)
				mask |= sigAPin;
			if ((dec & (1 << (4 - (2 * (i - 4))))) > 0)
				mask |= sigBPin;
		}
		else
		{
			if ((base & 1) > 0)
				mask |= sigAPin;
			if (dir == -1)
				mask |= sigBPin
		}

		HTSPBsetupIO(htspb, mask);
		mask = 0x00;
		HTSPBwriteIO(htspb, mask);

		mask = clockPin;
		while (HTSPBreadIO(htspb, mask) == 0x00);
	}

	mask = 0x00;
	HTSPBsetupIO(htspb, mask);

	writeDebugStreamLine("done");

	mask = sigAPin;
	while (HTSPBreadIO(htspb, mask) != 0x00);

	//ramp down

	mask = sigBPin;
	HTSPBsetupIO(htspb, mask);
	mask = 0x00;
	HTSPBwriteIO(htspb, mask);

	mask = sigAPin;
	while (HTSPBreadIO(htspb, mask) == 0x00);

	mask = 0x00;
	HTSPBsetupIO(htspb, mask);

	mask = sigAPin | clockPin;
	while (HTSPBreadIO(htspb, mask) != 0x00);

	mask = sigBPin;
	HTSPBsetupIO(htspb, mask);
	mask = 0x00;
	HTSPBwriteIO(htspb, mask);

	//stop robot
}
