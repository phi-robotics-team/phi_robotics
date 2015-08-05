#include <stdio.h>
#include <stdlib.h>
#include "int.h"
void write ( void )
{

    FILE *f;
    if(motorcount == 4)
    {


     f = fopen(name,"w");


    fprintf(f,"#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)\n#pragma config(Sensor, S1,     ,               sensorI2CMuxController)\n#pragma config(Motor,  mtr_S1_C1_1,%s,          tmotorTetrix, openLoop)\n",m1);
    fprintf(f,"#pragma config(Motor,  mtr_S1_C1_2,%s,          tmotorTetrix, openLoop)\n#pragma config(Motor,  mtr_S1_C2_1,%s,           tmotorTetrix, openLoop)\n#pragma config(Motor,  mtr_S1_C2_2,%s,           tmotorTetrix, openLoop)\n",m2,m3,m4);
    fprintf(f,"#pragma config(Motor,  mtr_S1_C3_1,%s,          tmotorTetrix, openLoop)\n#pragma config(Motor,  mtr_S1_C3_2,%s,          tmotorTetrix, openLoop)\n#pragma config(Motor,  mtr_S1_C4_1,%s,          tmotorTetrix, openLoop)\n",m5,m6,m7);
    fprintf(f,"#pragma config(Motor,  mtr_S1_C4_2,     ,          tmotorTetrix, openLoop)\n",m8);

    fprintf(f,"//Double click on the space above to write the pragma \n//this program was written  by Phi robotics ftc team 452 and 4322 please give credit to the team\n#include \"JoystickDriver.c\"  //Include file to handle the Bluetooth messages.");
    fprintf(f,"n\task drive();\n /////////////////////////////\ntask main()\n{\n   nxtDisplayTextLine(2, \"Waiting for start\");\n	waitForStart();   // wait for start of tele-op phase\n StartTask( drive );\n");
    fprintf(f,"float watchedmessage;\n	while(true)\n	{\n		watchedmessage = ntotalMessageCount; // grabs the number of Messages and names it watchedMessage\n		wait10Msec(25); // give the Messagecount time to change it changes every 50ms\n");
    fprintf(f,"		if(watchedmessage == ntotalMessageCount) // checks to see if the Message change if has not it is Disconnected\n		{                // if Disconnected it runs this\n			motor[mtr_S1_C1_1] = 0; // stops motor\n			motor[mtr_S1_C1_2] = 0;\n");
    fprintf(f,"			motor[mtr_S1_C2_1] = 0;\n			motor[mtr_S1_C2_2] = 0;\n			motor[mtr_S1_C3_1] = 0;\n			motor[mtr_S1_C3_2] = 0;\n			motor[mtr_S1_C4_1] = 0;\n			motor[mtr_S1_C4_2] = 0;\n");
    fprintf(f,"			StopTask(drive);\n			wait1Msec(10); //gives time to spot\n			StartTask(drive);\n			nxtDisplayTextLine(2, \"DISCONNECTED\"); //displays DISCONNECTED to tell you if you are Disconnected\n		}\n");
    fprintf(f,"		else//if the Message change you are connected\n		{\n			nxtDisplayTextLine(2, \"CONNECTED\"); //displays CONNECTED to tell you if everything is working\n		}\n	}\n}\n");
    fprintf(f,"task drive()\n{ int deadband = 10;\n float drivepower;\n  int cut = 10;\n	while (true)\n	{\n		getJoystickSettings(joystick);\n");
    fprintf(f,"		if(abs(joystick.joy1_y1) > deadband || abs(joystick.joy1_x1) > deadband)\n		{\n			if(abs(joystick.joy1_y1) > abs(joystick.joy1_x1))\n			{\n");
    fprintf(f,"				drivepower = (joystick.joy1_y1/cut) * abs(joystick.joy1_y1/cut);\n          if(drivepower > 100)\n          {\n          	drivepower = 100;\n          }\n          else if(drivepower < -100)\n");
    fprintf(f,"          {\n          	drivepower = -100;\n          }\n					motor[%s] =	drivepower;\n					motor[%s] =	drivepower;\n					motor[%s] = drivepower;\n",leftmotor,rightmotor,backleft);
    fprintf(f,"					motor[%s] = drivepower;\n			}\n			else if(abs(joystick.joy1_y1) <	 abs(joystick.joy1_x1))\n			{\n",backright);
    fprintf(f,"				drivepower = (joystick.joy1_x1/cut) * abs(joystick.joy1_x1/cut);\n				if(drivepower > 100)\n          {\n          	drivepower = 100;\n          }\n");
    fprintf(f,"          else if(drivepower < -100)\n          {\n          	drivepower = -100;\n          }\n				motor[%s] =	drivepower;\n				motor[%s] =	-1 * drivepower;\n",leftmotor,rightmotor);
    fprintf(f,"				motor[%s] = -1 * drivepower;\n				motor[%s] = drivepower;\n			}\n			else //if(abs(joystick.joy1_y1) < deadband || abs(joystick.joy1_x1) < deadband)\n			{\n				motor[%s] =	0;\n",backleft,backright,leftmotor);
    fprintf(f,"				motor[%s] =	0;\n				motor[%s] = 0;\n				motor[%s] = 0;\n				drivepower = 0;\n			}\n		}\n		else\n		{\n			motor[%s] =	0;\n",rightmotor,backleft,backright,leftmotor);
    fprintf(f,"			motor[%s] =	0;\n			motor[%s] = 0;\n			motor[%s] = 0;\n			drivepower = 0;\n		}\n	}\n}\n",rightmotor,backleft,backright);

     printf("your telop has been created it is where you ran this program named \"%s\"\n",name);

     fclose(f);
    }
    else if(motorcount == 2)
    {



    f = fopen(name,"w");
    fprintf(f,"#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)\n#pragma config(Sensor, S1,     ,               sensorI2CMuxController)\n#pragma config(Motor,  mtr_S1_C1_1,%s,          tmotorTetrix, openLoop)\n",m1);
    fprintf(f,"#pragma config(Motor,  mtr_S1_C1_2,%s,          tmotorTetrix, openLoop)\n#pragma config(Motor,  mtr_S1_C2_1,%s,           tmotorTetrix, openLoop)\n#pragma config(Motor,  mtr_S1_C2_2,%s,           tmotorTetrix, openLoop)\n",m2,m3,m4);
    fprintf(f,"#pragma config(Motor,  mtr_S1_C3_1,%s,          tmotorTetrix, openLoop)\n#pragma config(Motor,  mtr_S1_C3_2,%s,          tmotorTetrix, openLoop)\n#pragma config(Motor,  mtr_S1_C4_1,%s,          tmotorTetrix, openLoop)\n",m5,m6,m7);
    fprintf(f,"#pragma config(Motor,  mtr_S1_C4_2,     ,          tmotorTetrix, openLoop)\n",m8);

    fprintf(f,"//Double click on the space above to write the pragma \n//this program was written by Phi robotics ftc team 452 and 4322 please give credit to the team\n#include \"JoystickDriver.c\"  //Include file to handle the Bluetooth messages.");
    fprintf(f,"\ntask drive();\n /////////////////////////////\ntask main()\n{\n  nxtDisplayTextLine(2, \"Waiting for start\");\n	waitForStart();   // wait for start of tele-op phase\n StartTask( drive );\n");
    fprintf(f,"float watchedmessage;\n	while(true)\n	{\n		watchedmessage = ntotalMessageCount; // grabs the number of Messages and names it watchedMessage\n		wait10Msec(25); // give the Messagecount time to change it changes every 50ms\n");
    fprintf(f,"		if(watchedmessage == ntotalMessageCount) // checks to see if the Message change if has not it is Disconnected\n		{                // if Disconnected it runs this\n			motor[mtr_S1_C1_1] = 0; // stops motor\n			motor[mtr_S1_C1_2] = 0;\n");
    fprintf(f,"			motor[mtr_S1_C2_1] = 0;\n			motor[mtr_S1_C2_2] = 0;\n			motor[mtr_S1_C3_1] = 0;\n			motor[mtr_S1_C3_2] = 0;\n			motor[mtr_S1_C4_1] = 0;\n			motor[mtr_S1_C4_2] = 0;\n");
    fprintf(f,"			StopTask(drive);\n			wait1Msec(10); //gives time to spot\n			StartTask(drive);\n			nxtDisplayTextLine(2, \"DISCONNECTED\"); //displays DISCONNECTED to tell you if you are Disconnected\n		}\n");
    fprintf(f,"		else//if the Message change you are connected\n		{\n			nxtDisplayTextLine(2, \"CONNECTED\"); //displays CONNECTED to tell you if everything is working\n		}\n	}\n}\n");
    fprintf(f,"task drive()\n{\n  int deadband = 10;\n float drivepower;\n  int cut = 10;\n	while (true)\n	{\n		getJoystickSettings(joystick);\n");
    fprintf(f,"		if(abs(joystick.joy1_y1) > deadband || abs(joystick.joy1_x1) > deadband)\n		{\n			if(abs(joystick.joy1_y1) > abs(joystick.joy1_x1))\n			{\n");
    fprintf(f,"				drivepower = (joystick.joy1_y1/cut) * abs(joystick.joy1_y1/cut);\n          if(drivepower > 100)\n          {\n          	drivepower = 100;\n          }\n          else if(drivepower < -100)\n");
    fprintf(f,"          {\n          	drivepower = -100;\n          }\n										motor[%s] =	drivepower;					\n", rightmotor);
    fprintf(f,"					motor[%s] = drivepower;\n			}\n			else if(abs(joystick.joy1_y1) <	 abs(joystick.joy1_x1))\n			{\n", leftmotor);
    fprintf(f,"				drivepower = (joystick.joy1_x1/cut) * abs(joystick.joy1_x1/cut);\n				if(drivepower > 100)\n          {\n          	drivepower = 100;\n          }\n");
    fprintf(f,"          else if(drivepower < -100)\n          {\n          	drivepower = -100;\n          }\n				motor[%s] =	drivepower;\n				",leftmotor);
    fprintf(f,"				motor[%s] = -1 * drivepower;\n							}\n			else 			{\n				motor[%s] =	0;\n",rightmotor, leftmotor);
    fprintf(f,"				motor[%s] =	0;\n				drivepower = 0;\n			}\n		}\n		else\n		{\n			motor[%s] =	0;\n",rightmotor, leftmotor);
    fprintf(f,"			motor[%s] = 0;\n			drivepower = 0;\n		}\n	}\n}\n",rightmotor);

     printf("your telop has been created it is where you ran this program named \"%s\"\n",name);
     fclose(f);
    }
    else
    {
     printf("error program only works with two or four wheel drive\n");

    }
}
