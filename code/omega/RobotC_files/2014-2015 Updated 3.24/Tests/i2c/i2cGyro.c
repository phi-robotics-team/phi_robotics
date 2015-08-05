#include "i2c.h"

#define CTRL_REG1 0x20
#define CTRL_REG2 0x21
#define CTRL_REG3 0x22
#define CTRL_REG4 0x23
#define CTRL_REG5 0x24

int L3G4200D_Address = 105; //I2C address of the L3G4200D

float x;
float y;
float z;

void writeRegister(int deviceAddress, byte address, byte val) {
    i2c_beginTransmission(deviceAddress); // start transmission to device
    i2c_write(address);       // send register address
    i2c_write(val);         // send value to write
    i2c_endTransmission();     // end transmission
}

int readRegister(int deviceAddress, byte address){

    int v;
    i2c_beginTransmission(deviceAddress);
    i2c_write(address); // register to read
    i2c_endTransmission();

    i2c_requestFrom(deviceAddress, 1); // read a byte

    while(!i2c_available()) {
        // waiting
    }

    v = i2c_read();
    return v;
}

void getGyroValues(){

  byte xMSB = readRegister(L3G4200D_Address, 0x29);
  byte xLSB = readRegister(L3G4200D_Address, 0x28);
  x = ((xMSB << 8) | xLSB)/14.286;

  byte yMSB = readRegister(L3G4200D_Address, 0x2B);
  byte yLSB = readRegister(L3G4200D_Address, 0x2A);
  y = ((yMSB << 8) | yLSB)/14.286;

  byte zMSB = readRegister(L3G4200D_Address, 0x2D);
  byte zLSB = readRegister(L3G4200D_Address, 0x2C);
  z = ((zMSB << 8) | zLSB)/14.286;
}

void setupL3G4200D(int scale){
  //From  Jim Lindblom of Sparkfun's code

  // Enable x, y, z and turn off power down:
  writeRegister(L3G4200D_Address, CTRL_REG1, 0b00001111);

  // If you'd like to adjust/use the HPF, you can edit the line below to configure CTRL_REG2:
  writeRegister(L3G4200D_Address, CTRL_REG2, 0b00000000);

  // Configure CTRL_REG3 to generate data ready interrupt on INT2
  // No interrupts used on INT1, if you'd like to configure INT1
  // or INT2 otherwise, consult the datasheet:
  writeRegister(L3G4200D_Address, CTRL_REG3, 0b00001000);

  // CTRL_REG4 controls the full-scale range, among other things:

  if(scale == 250){
    writeRegister(L3G4200D_Address, CTRL_REG4, 0b00000000);
  }else if(scale == 500){
    writeRegister(L3G4200D_Address, CTRL_REG4, 0b00010000);
  }else{
    writeRegister(L3G4200D_Address, CTRL_REG4, 0b00110000);
  }

  // CTRL_REG5 controls high-pass filtering of outputs, use it
  // if you'd like:
  writeRegister(L3G4200D_Address, CTRL_REG5, 0b00000000);
}

void setup(){

  i2c_begin(htspb, 0, 1);

  setupL3G4200D(2000); // Configure L3G4200  - 250, 500 or 2000 deg/sec

  wait10Msec(150); //wait for the sensor to be ready
}

void loop1(){
	ClearTimer(T1);
	getGyroValues();  // This will update x, y, and z with new values

	writeDebugStreamLine("X: %f, Y: %f, Z: %f", x, y, z);
	writeDebugStreamLine("Time: %d", time1[T1]);
  //wait10Msec(10); //Just here to slow down the serial to make it more readable
}

void Turn( float turnDegrees )
{
	// Store new bias
	int state = 2;
	//float GyroBias = 0;
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
	motor[leftRear] = -rotDirection * motorSpeed;
	motor[leftFront] = -rotDirection * motorSpeed;
	motor[rightRear] = rotDirection * motorSpeed;
	motor[rightFront] = rotDirection * motorSpeed;
	wait1Msec(10);

	// reset the back motor encoders to zero
	nMotorEncoder[rightRear] = 0;
	nMotorEncoder[leftRear] = 0;

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
		getGyroValues();
		GyroNew = -((float)z - GyroBias);

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

		motor[leftRear] = rotDirection * motorSpeed;
		motor[leftFront] = rotDirection * motorSpeed;
		motor[rightRear] = -rotDirection * motorSpeed;
		motor[rightFront] = -rotDirection * motorSpeed; // side moves forward for (+) CCW rotation

		if( time100[T3] > 50 ) break; // if the bot is not done turning in 5 sec, quit
			wait1Msec(15); // wait 20 ms to allow a reasonable period for the integration

	} // End while rotation remaining

	// since we have now reached the target rotation (the while loop is done), stop all drive motors

	motor[leftRear] = 0;
	motor[leftFront] = 0;
	motor[rightRear] = 0;
	motor[rightFront] = 0;

	// reset the back motor encoders to zero
	nMotorEncoder[rightRear] = 0;
	nMotorEncoder[leftRear] = 0;

} // End of Turn_Gyro()
