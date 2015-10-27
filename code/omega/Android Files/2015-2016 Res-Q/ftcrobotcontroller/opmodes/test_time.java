package com.qualcomm.ftcrobotcontroller.opmodes;

import android.os.SystemClock;
import com.qualcomm.robotcore.eventloop.opmode.LinearOpMode;

/**
 * Created by phi on 10/8/2015.
 */
public class test_time extends LinearOpMode {

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

