package com.qualcomm.ftcrobotcontroller.opmodes;


import android.os.SystemClock;
import com.qualcomm.robotcore.eventloop.opmode.LinearOpMode;
import com.qualcomm.robotcore.hardware.GyroSensor;


import java.util.Date;
//import com.qualcomm.robotcore.util.ElapsedTime;

/**
 * Created by thcox on 10/2/2015.
 */
public class test_gyro_sensor extends LinearOpMode {

    //time = new ElaspedTime();
    GyroSensor gyro;


    @Override
    public void runOpMode() throws InterruptedException {
        double GyroVariable;

        gyro = hardwareMap.gyroSensor.get("gyro");


        //time.startTime();
        while (opModeIsActive()) {


            GyroVariable = gyro.getRotation();
            telemetry.addData("gyro ", GyroVariable);

            waitOneFullHardwareCycle();
            //time.reset();
        }
    }

}
