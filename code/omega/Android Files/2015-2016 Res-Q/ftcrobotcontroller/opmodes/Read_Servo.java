//package com.qualcomm.ftcrobotcontroller.opmodes;

//import com.qualcomm.ftccommon.DbgLog;
//import com.qualcomm.robotcore.eventloop.opmode.LinearOpMode;
//import com.qualcomm.robotcore.hardware.DcMotor;
//import com.qualcomm.robotcore.hardware.DcMotorController;
//import com.qualcomm.robotcore.hardware.GyroSensor;
//import com.qualcomm.robotcore.hardware.Servo;

/**
 * Created by phi on 12/6/2015.
 */
//public class Read_Servo {
    //we want to read the position of the servo and have it printed to the phone
    //servo_6 is the name of the servo
    //Need to declare what servo_6 is.... DcMotor? Servo?

    //public class Servo {

        //Servo servo_6;
         //so far so good....I hope.
        //looking online, there seem to be two ways to get the position of the servo.  Both aren't working.  I've commented them both below.

        //public double getPosition();
        //servo_6.getController().getServoPosition(servo_6.getChannel());

    //telemetry.addData("servo_6", servo_6);
//the telemetry print statement isn't working either... I must have done something wrong how I first set up my code...

    //}

//}

//attempting to reformat old code to see if that will work... I have made no changes yet...unsure what needs to be changed

package com.qualcomm.ftcrobotcontroller.opmodes;

import android.os.SystemClock;
import com.qualcomm.robotcore.eventloop.opmode.LinearOpMode;

/**
 * Created by phi on 10/8/2015.
 */
public class Read_Servo extends LinearOpMode {

    double tp0;
    double tp1;

    @Override
    public void runOpMode() throws InterruptedException {
        waitForStart();

        while (opModeIsActive())  {
            long tnt = System.nanoTime();
            // double t0 = tnt / 1000000000;
            double t1 = SystemClock.uptimeMillis()/1000.0;

            // double dt0 = t0 - tp0;
            double dt1 = t1 - tp1;

            telemetry.addData("dt1", "dt1 " + String.format("%.12f", dt1));
            //telemetry.addData("dt0", "dt0 " + String.format("%.12f", dt0));
            telemetry.addData("t1",t1);
            //telemetry.addData("t0",t0);
            telemetry.addData("tp1",tp1);
            //telemetry.addData("tp0",tp0);

            //tp0 = t0;
            tp1= t1;

            waitOneFullHardwareCycle();
        }
    }
}

