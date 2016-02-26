package com.qualcomm.ftcrobotcontroller.opmodes;


import com.qualcomm.ftccommon.DbgLog;
import com.qualcomm.robotcore.eventloop.opmode.LinearOpMode;
import com.qualcomm.robotcore.hardware.DcMotor;
import com.qualcomm.robotcore.hardware.DcMotorController;

public class read_encoder extends LinearOpMode {

    DcMotor leftFront;
    DcMotor leftRear;
    DcMotor rightFront;
    DcMotor rightRear;
    DcMotorController dc_1;
    DcMotorController dc_2;
    DcMotorController.DeviceMode devMode_a;
    DcMotorController.DeviceMode devMode_b;

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
        leftFront.setDirection(DcMotor.Direction.REVERSE);
        leftRear.setDirection(DcMotor.Direction.REVERSE);

        leftFront.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);
        rightFront.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);
        wait1Msec(20);
        leftFront.setChannelMode(DcMotorController.RunMode.RUN_USING_ENCODERS);
        rightFront.setChannelMode(DcMotorController.RunMode.RUN_USING_ENCODERS);
        leftRear.setChannelMode(DcMotorController.RunMode.RUN_USING_ENCODERS);
        rightRear.setChannelMode(DcMotorController.RunMode.RUN_USING_ENCODERS);
        wait1Msec(20);

        // wait for the start button to be pressed.
        waitForStart();



        dc_1.setMotorControllerDeviceMode(DcMotorController.DeviceMode.WRITE_ONLY);
        dc_2.setMotorControllerDeviceMode(DcMotorController.DeviceMode.WRITE_ONLY);
        wait1Msec(20);
        double t_old=this.time;
        double t1=t_old;
        double power = 0.9;
       double  dist = 40;
        long rightFrontEncoder = 0;
        long leftFrontEncoder = 0;

        while (opModeIsActive()) {


            /* while (t1 - t_old <= 2.0) {
                t1=this.time;
                leftFront.setPower(power);
                rightFront.setPower(power);
                leftRear.setPower(power);
                rightRear.setPower(power);
                wait1Msec(20);
            } */

          //  if (t1 == t_old) DbgLog.msg(String.format("Data2-Time- %.03f", t1));
            t1=this.time;
          //  DbgLog.msg(String.format("Data1-Time- %.03f", t1));
            double cnt_target = cnts_distin * dist;
            telemetry.addData("cnt_target", (int) cnt_target);

           leftFront.setPower(power);
            rightFront.setPower(power);
            leftRear.setPower(power);
            rightRear.setPower(power);
            wait1Msec(20);

            dc_1.setMotorControllerDeviceMode(DcMotorController.DeviceMode.READ_ONLY);
            dc_2.setMotorControllerDeviceMode(DcMotorController.DeviceMode.READ_ONLY);
          //  devMode_a = dc_1.getMotorControllerDeviceMode();
         //   devMode_b = dc_2.getMotorControllerDeviceMode();
           // if (devMode_b == DcMotorController.DeviceMode.READ_ONLY) DbgLog.msg(String.format("Data3-Time- %.03f", t1));
        //    telemetry.addData("t1-2", t1);
         //   telemetry.addData("devMode_a", devMode_a);
         //   telemetry.addData("devMode_b",devMode_b);

            wait1Msec(20);

            while (rightFrontEncoder < cnt_target & leftFrontEncoder < cnt_target) {
                // long rightFrontEncoder = 1;
                //   long leftFrontEncoder = 1;
                rightFrontEncoder = rightFront.getCurrentPosition();
                leftFrontEncoder = leftFront.getCurrentPosition();
                telemetry.addData("t1", t1);
                telemetry.addData("t_old", t_old);
                telemetry.addData("rightFrontEncoder", rightFrontEncoder);
                telemetry.addData("leftFrontEncoder", leftFrontEncoder);
                DbgLog.msg(String.format("Data2-Time- %.03f", t1));
                DbgLog.msg(String.format("Data2-RightFrontEncoder- %.03f", (float) rightFrontEncoder));
                DbgLog.msg(String.format("Data2-LeftFrontEncoder- %.03f", (float) leftFrontEncoder));
                wait1Msec(20);


            }

            dc_1.setMotorControllerDeviceMode(DcMotorController.DeviceMode.WRITE_ONLY);
            dc_2.setMotorControllerDeviceMode(DcMotorController.DeviceMode.WRITE_ONLY);
            wait1Msec(20);

              //  while (t1 - t_old > 5.0) {
                    power = 0.0;
                    leftFront.setPower(power);
                    rightFront.setPower(power);
                    leftRear.setPower(power);
                    rightRear.setPower(power);
             //       waitOneFullHardwareCycle();
             //   }
            waitOneFullHardwareCycle();
        }


    }
    void wait1Msec(long time) throws InterruptedException {
        Thread.sleep(time);
        return;
    }
}

