#include "hitechnic-superpro.h"

void Move(float dist)
{
	//start robot

	int clockPin = 0x01; //Pin 0
	int sigAPin = 0x02; //Pin 1
	int sigBPin = 0x04; //Pin 2
	ubyte mask = 0;

	mask = clock | sigAPin;
	HTSPBsetupIO(htspb, mask);
	mask = 0x00;
	HTSPBwriteIO(htspb, mask);
	
	mask = sigBPin;
	while (HTSPBreadIO(htspb, mask) == sigBPin);

	float place = 100;
	for (int i = 0; i < 5; i++)
	{
		int temp = (int)(dist / place) - ((int)((int)(dist / place) / 10) * 10);
		for (int j = 0; j < 2; j++)
		{
			mask = clockPin;
			HTSPBsetupIO(htspb, mask);
			mask = 0x00;
			HTSPBwriteIO(htspb, mask);
			
			if ((temp >> (2 * j)) & 0x01 > 0)
				mask |= sigAPin;
			if ((temp >> ((2 * j) + 1)) & 0x01 > 0)
				mask |= sigBPin;

			HTSPBsetupIO(htspb, mask);
			mask = 0x00;
			HTSPBwriteIO(htspb, mask);

			mask = clockPin;
			while (HTSPBreadIO(htspb, mask) == 0x00);
		}
		place /= 10;
	}

	mask = 0x00;
	HTSPBsetupIO(htspb, mask);

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