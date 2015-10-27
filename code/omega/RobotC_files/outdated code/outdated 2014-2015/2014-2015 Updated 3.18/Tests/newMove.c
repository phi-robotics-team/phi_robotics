//Move Function
float countsPerInch = 9.823522388059701 * 2;
void Move(float Distance, float Speed)
{
	float distTrav = 0.0, time = 0.0, powerShiftConst = 0.2, speedPercent = 0.0;
	float leftPower = 0.0, rightPower = 0.0, leftSpeed = 0.0, rightSpeed = 0.0;
	long leftEncodCount = 0.0, rightEncodCount = 0.0, prevLeftEncodCount = 0.0, prevRightEncodCount = 0.0;

	float direction = (float)sgn(Distance) * Speed;
	Distance = abs(Distance);
	Distance *= countsPerInch;
	//Speed *= countsPerInch;

	leftPower = 0;
	rightPower = 0;
	nMotorEncoder[rightRear] = 0;
	nMotorEncoder[leftRear] = 0;
	ClearTimer(T1);
	motor[leftFront] = leftPower;
	motor[leftRear] = leftPower;
	motor[rightFront] = rightPower;
	motor[rightRear] = rightPower;
	while (abs(distTrav) < Distance)
	{
		time = (float)time1[T1] / (float)1000;
		leftEncodCount = (abs(nMotorEncoder[leftRear]) > (100 + abs(prevLeftEncodCount))) ? prevLeftEncodCount : nMotorEncoder[leftRear];
		rightEncodCount = (abs(nMotorEncoder[rightRear]) > (100 + abs(prevRightEncodCount))) ? prevRightEncodCount : nMotorEncoder[rightRear];

		speedPercent = -1 * log(distTrav/Distance);
		if (speedPercent > 1)
			speedPercent = 1;
		Speed *= speedPercent;
		distTrav = (rightEncodCount);
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
		motor[leftFront] = direction * leftPower;
		motor[leftRear] = direction * leftPower;
		motor[rightFront] = direction * rightPower;
		motor[rightRear] = direction * rightPower;

		prevLeftEncodCount = nMotorEncoder[leftRear];
		prevRightEncodCount = nMotorEncoder[rightRear];

		ClearTimer(T1);
		//wait1Msec(10);
		//writeDebugStreamLine("Right: %d", rightEncodCount);
		//writeDebugStreamLine("Left: %d", leftEncodCount);
	}
	motor[leftFront] = 0;
	motor[leftRear] = 0;
	motor[rightFront] = 0;
	motor[rightRear] = 0;
}
