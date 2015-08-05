#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     Gyro,           sensorI2CHiTechnicGyro)
#pragma config(Sensor, S3,     IR,             sensorHiTechnicIRSeeker600)
#pragma config(Sensor, S4,     sonar,          sensorSONAR)
#pragma config(Motor,  mtr_S1_C1_1,     B_R,           tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     B_L,           tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     block_arm,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     Flag_Arm,      tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_1,     motorH,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     Winch,         tmotorTetrix, openLoop, reversed)
#pragma config(Servo,  srvo_S1_C4_1,    Hook,                 tServoStandard)
#pragma config(Servo,  srvo_S1_C4_2,    Claw,                 tServoStandard)
#pragma config(Servo,  srvo_S1_C4_3,    release,              tServoStandard)
#pragma config(Servo,  srvo_S1_C4_4,    aim1,                 tServoStandard)
#pragma config(Servo,  srvo_S1_C4_5,    aim2,                 tServoStandard)
#pragma config(Servo,  srvo_S1_C4_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
int moveRunning = 0;

#include "move_2_wheel.c"

task main()
{
	Move(5,50);
}
