package com.qualcomm.ftcrobotcontroller.opmodes;

import android.os.SystemClock;
import com.qualcomm.robotcore.eventloop.opmode.LinearOpMode;
import java.util.Date;
//import com.qualcomm.robotcore.util.ElapsedTime;

/**
 * Created by thcox on 10/2/2015.
 */
public class test_time_3 extends LinearOpMode {

     //time = new ElaspedTime();

    @Override
    public void runOpMode() throws InterruptedException {



        // wait for the start button to be pressed.
        waitForStart();
        double tp0 = 0.0;
        double tp1 = 0.0;
        double ttp = 0.0;
        long tpn = (long) 0.0;

        //time.startTime();
        while (opModeIsActive()) {
            long tntn = System.nanoTime();
            double tt=this.time;
            double tnt=new Date().getTime(); // start time
            long tn = tntn / (long) 1000000.0;
            double t0 = tnt / 1000.0;
            double t1 = SystemClock.uptimeMillis() / 1000.0;
            //double = System.currentTimeInMillis();


            double dt0 = t0 - tp0;
            double dt1 = t1 - tp1;
            long dtn = tn - tpn;
            double dtt= tt - ttp;
            telemetry.addData("dt1 ", dt1);
            telemetry.addData("dt0 ", dt0);
            telemetry.addData("dtn", dtn);
            telemetry.addData("dtt",dtt);
            telemetry.addData("tt",tt);
            telemetry.addData("t0 ",t0);
            telemetry.addData("t1 ", t1);
            telemetry.addData("tn ", tn);
            tp0 = t0;
            tp1 = t1;
            tpn = tn;
            ttp= tt;
            waitOneFullHardwareCycle();
            //time.reset();
        }
    }
}
