#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S2,     Gyro,           sensorI2CHiTechnicGyro)
#pragma config(Sensor, S3,     IR,             sensorHiTechnicIRSeeker600)
#pragma config(Sensor, S4,     sonar,          sensorNone)
#pragma config(Motor,  mtr_S1_C1_1,     Right_Side,    tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     Left_Side,     tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     Block_Arm,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     Flag_Arm,      tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_1,     lights,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     Winch,         tmotorTetrix, openLoop, reversed)
#pragma config(Servo,  srvo_S1_C4_1,    Hook,                 tServoStandard)
#pragma config(Servo,  srvo_S1_C4_2,    Arm,                  tServoStandard)
#pragma config(Servo,  srvo_S1_C4_3,    autoBlock,            tServoStandard)
#pragma config(Servo,  srvo_S1_C4_4,    rake,                 tServoStandard)
#pragma config(Servo,  srvo_S1_C4_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_6,    servo6,               tServoNone)

task main()
{
	while (true)
	{
		motor[lights] = 100;
	}
}
