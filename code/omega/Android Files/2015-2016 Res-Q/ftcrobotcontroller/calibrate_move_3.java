package com.qualcomm.ftcrobotcontroller.opmodes;


import android.hardware.Sensor;
import android.hardware.SensorEvent;

import com.qualcomm.ftccommon.DbgLog;
import com.qualcomm.robotcore.eventloop.opmode.LinearOpMode;
import com.qualcomm.robotcore.hardware.DcMotor;
import com.qualcomm.robotcore.hardware.DcMotorController;
import com.qualcomm.robotcore.hardware.GyroSensor;

public class calibrate_move_3 extends LinearOpMode {

    DcMotor leftFront;
    DcMotor leftRear;
    DcMotor rightFront;
    DcMotor rightRear;
    DcMotorController dc_1;
    DcMotorController dc_2;
    DcMotorController.DeviceMode devMode_a;
    DcMotorController.DeviceMode devMode_b;
    // GyroSensor gyro;



    // wheel and motor info to calculate the # of counts on encoder per inch of distance 'cnts_distin'
    double diam = 4.0;
    long cnts_motorrev = 1440;
    //long cnts_motorrev = 1120;
    double dist_wheelrev = 3.1416 * diam;
    double motorrev_wheelrev = 1.0;
    double cnts_distin = cnts_motorrev * motorrev_wheelrev / dist_wheelrev;





    @Override
    public void runOpMode() throws InterruptedException {
        rightFront = hardwareMap.dcMotor.get("rightFront");
        rightRear = hardwareMap.dcMotor.get("rightRear");
        leftFront = hardwareMap.dcMotor.get("leftFront");
        leftRear = hardwareMap.dcMotor.get("leftRear");
        dc_1 = hardwareMap.dcMotorController.get("dc_1");
        dc_2 = hardwareMap.dcMotorController.get("dc_2");
        //gyro = hardwareMap.gyroSensor.get("gyro");
        leftFront.setDirection(DcMotor.Direction.REVERSE);
        leftRear.setDirection(DcMotor.Direction.REVERSE);
        //double gyroNew_m;
        //double gyroBias_m;

        // wait for the start button to be pressed.
        waitForStart();

        double power = 0.10;
        long tdly = 50;
        // gyroBias_m= gyro.getRotation();

        // I am interested in calibrating this controller mode because it is linear
       /* leftFront.setChannelMode(DcMotorController.RunMode.RUN_USING_ENCODERS);
        rightFront.setChannelMode(DcMotorController.RunMode.RUN_USING_ENCODERS);
        leftRear.setChannelMode(DcMotorController.RunMode.RUN_USING_ENCODERS);
        rightRear.setChannelMode(DcMotorController.RunMode.RUN_USING_ENCODERS); */
        leftFront.setChannelMode(DcMotorController.RunMode.RUN_WITHOUT_ENCODERS);
        rightFront.setChannelMode(DcMotorController.RunMode.RUN_WITHOUT_ENCODERS);
        leftRear.setChannelMode(DcMotorController.RunMode.RUN_WITHOUT_ENCODERS);
        rightRear.setChannelMode(DcMotorController.RunMode.RUN_WITHOUT_ENCODERS);
        wait1Msec(tdly);
        //int pow_s=0;
        // double k_pow=.01;
        double power_l=power;
        double power_r=power;

        //Runs motors at very low power to stop backlash
       /* double motorSpeed = .05;
        leftRear.setPower( motorSpeed);
        leftFront.setPower(motorSpeed);
        rightRear.setPower(motorSpeed);
        rightFront.setPower(motorSpeed);
        wait1Msec(tdly);*/

        while (opModeIsActive()) {


            //Runs motors at very low power to stop backlash
            // leftRear.setPower(.05);
            // leftFront.setPower(.05);
            // rightRear.setPower(.05);
            // rightFront.setPower(.05);
            // wait1Msec(tdly);

            double t_old=this.time;
            // double t_old= System.currentTimeMillis()/1000.;
            double t1 = t_old;

            while (t1 - t_old <= 2.0) {
                t1=this.time;
                //gyroNew_m = -(gyro.getRotation()-gyroBias_m);
                //   t1= System.currentTimeMillis()/1000.;
                //if (gyroNew_m < 0) pow_s = -1;
                //else pow_s = 1;

                //k_pow=0.;

                //power_l=power + pow_s*k_pow*gyroNew_m;
                // power_r=power - pow_s*k_pow*gyroNew_m;
                //double del_pow=pow_s*k_pow*gyroNew_m;
                // if (power_l > 1.0) power_l=.99;
                // if (power_l < -1.0) power_l = -.99;
                // if (power_r > 1.0) power_r = .99;
                //if (power_r < -1.0) power_r = -.99;
                power_l=power;
                power_r=power;

                leftFront.setPower(power_l);
                rightFront.setPower(power_r);
                leftRear.setPower(power_l);
                rightRear.setPower(power_r);
                telemetry.addData("t1", t1 - t_old);
                //telemetry.addData("del_pow", del_pow);
                // telemetry.addData("gyroNew_m", gyroNew_m);

                telemetry.addData("power_l",power_l);
                telemetry.addData("power_r",power_r);

                DbgLog.msg(String.format("Data2-Time- %.03f", t1 - t_old));
                /*DbgLog.msg(String.format("Data2-del_pow- %.03f", del_pow));
                DbgLog.msg(String.format("Data2-GyroNew_m- %.03f", gyroNew_m));*/
                DbgLog.msg(String.format("Data2-power_l- %.03f", power_l));
                DbgLog.msg(String.format("Data2-power_r- %.03f", power_r));
                wait1Msec(tdly);
            }

            power =0.0;
            leftFront.setPower(power);
            rightFront.setPower(power);
            leftRear.setPower(power);
            rightRear.setPower(power);



            //DbgLog.msg(String.format("Data2-Time- %.03f", t1));
           /* telemetry.addData("Accel_linear", Sensor.TYPE_LINEAR_ACCELERATION);
            telemetry.addData("accel_uncal", Sensor.TYPE_ACCELEROMETER);
            telemetry.addData("significant motion", Sensor.TYPE_SIGNIFICANT_MOTION); */
            telemetry.addData("t1", t1-t_old);


// set the mode of controller back
            leftFront.setChannelMode(DcMotorController.RunMode.RUN_WITHOUT_ENCODERS);
            rightFront.setChannelMode(DcMotorController.RunMode.RUN_WITHOUT_ENCODERS);
            leftRear.setChannelMode(DcMotorController.RunMode.RUN_WITHOUT_ENCODERS);
            rightRear.setChannelMode(DcMotorController.RunMode.RUN_WITHOUT_ENCODERS);

            waitOneFullHardwareCycle();
        }


    }
    void wait1Msec(long time) throws InterruptedException {
        Thread.sleep(time);
        return;
    }
}
