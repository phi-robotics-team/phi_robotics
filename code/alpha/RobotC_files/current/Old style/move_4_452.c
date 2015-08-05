void Move(float Distance, float Speed)
{
	float countsPerInch = 18.482;

	float distTrav = 0.0, time = 0.0, powerShiftConst = 0.2, speedPercent = 0.0;
	float leftPower = 0.0, rightPower = 0.0, leftSpeed = 0.0, rightSpeed = 0.0;
	long leftEncodCount = 0.0, rightEncodCount = 0.0, prevLeftEncodCount = 0.0, prevRightEncodCount = 0.0;

	float direction = (float)sgn(Distance) * Speed;
	Distance = abs(Distance);
	Distance *= countsPerInch;
	//Speed *= countsPerInch;

	leftPower = 5;
	rightPower = 5;
	nMotorEncoder[rightDrive] = 0;
	nMotorEncoder[leftDrive] = 0;
	ClearTimer(T1);
	motor[leftDrive] = leftPower;
	motor[rightDrive] = rightPower;

	while (abs(distTrav) < Distance)
	{
		time = (float)time1[T1] / (float)1000;
		leftEncodCount = nMotorEncoder[leftDrive];
		rightEncodCount = nMotorEncoder[rightDrive];

		speedPercent = -1 * log(distTrav/Distance);
		if (speedPercent > 1)
			speedPercent = 1;
		Speed *= speedPercent;
		distTrav = (leftEncodCount + rightEncodCount) / 2;
		/*leftSpeed = (leftEncodCount - prevLeftEncodCount) / time;
		rightSpeed = (rightEncodCount - prevRightEncodCount) / time;

		if (leftSpeed == 0)
			leftSpeed = Speed;
		if (rightSpeed == 0)
			rightSpeed = Speed;

		leftPower += (Speed - leftSpeed) * powerShiftConst;
		rightPower += (Speed - rightSpeed) * powerShiftConst;

		if (leftPower > 100)
			leftPower = 100;
		if (rightPower > 100)
			rightPower = 100;*/

		leftPower = 100;
		rightPower = 100;
		motor[leftDrive] = direction * leftPower;
		motor[rightDrive] = direction * rightPower;

		prevLeftEncodCount = nMotorEncoder[leftDrive];
		prevRightEncodCount = nMotorEncoder[rightDrive];

	//	writeDebugStreamLine("encoder: %f ", prevLeftEncodCount);
		//writeDebugStreamLine("right: %f ", rightSpeed);
		//writeDebugStreamLine("%f", Speed);
		ClearTimer(T1);
		//wait1Msec(10);
		//writeDebugStreamLine("distTrav: %d", distTrav);
	}
	motor[leftDrive] = 0;
	motor[rightDrive] = 0;
}
