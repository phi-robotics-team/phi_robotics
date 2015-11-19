package com.qualcomm.ftcrobotcontroller.opmodes;

import com.qualcomm.robotcore.eventloop.opmode.LinearOpMode;
import com.qualcomm.robotcore.hardware.DcMotor;
import com.qualcomm.robotcore.hardware.DcMotorController;


/**
 * Created by thcox on 10/26/2015.
 */
public class test_MoveEncoder extends LinearOpMode {

    DcMotorController.DeviceMode devMode_a;
    DcMotorController.DeviceMode devMode_b;
    DcMotor leftFront;
    DcMotor leftRear;
    DcMotor rightFront;
    DcMotor rightRear;
    DcMotorController dc_1;
    DcMotorController dc_2;

    int rightFrontCurrentEncoder;
    int leftFrontCurrentEncoder;
    int rightRearCurrentEncoder;
    int leftRearCurrentEncoder;

    double diam = 4.0;
    long cnts_motorrev = 1440;
    //long cnts_motorrev = 1120;
    double dist_wheelrev = 3.1416 * diam;
    double motorrev_wheelrev = 1.0;
    double cnts_distin = cnts_motorrev * motorrev_wheelrev / dist_wheelrev;

    int numOpLoops;
    int rightFrontCurEnc;
    int rightRearCurEnc;
    int leftFrontCurEnc;
    int leftRearCurEnc;
    int leftFrontTarPos;
    int leftRearTarPos;
    int rightFrontTarPos;
    int ii=0;

    @Override
    public void runOpMode() throws InterruptedException {

        leftFront = hardwareMap.dcMotor.get("leftFront");
        rightFront = hardwareMap.dcMotor.get("rightFront");
        leftRear = hardwareMap.dcMotor.get("leftRear");
        rightRear = hardwareMap.dcMotor.get("rightRear");
        dc_1 = hardwareMap.dcMotorController.get("dc_1");
        dc_2 = hardwareMap.dcMotorController.get("dc_2");
        devMode_a = DcMotorController.DeviceMode.WRITE_ONLY;
        devMode_b = DcMotorController.DeviceMode.WRITE_ONLY;

        leftFront.setDirection(DcMotor.Direction.REVERSE);
        leftRear.setDirection(DcMotor.Direction.REVERSE);


        waitForStart();

        int jj=0;
/*
        while (opModeIsActive()) {

            jj=jj+1;
            double dist_in = 75.0;
            double motor_power = 1.0;
            // if (ii == 0) MoveEncoder(dist_in, motor_power);

            telemetry.addData("jj",jj);

            waitOneFullHardwareCycle();
        }*/


        double power = 1.0;
        double dist = 10.0;
        double rightFrontCurrentEncoder = 0;
        double leftFrontCurrentEncoder = 0;

        leftFront.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);
        rightFront.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);
        // leftRear.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);
        // rightRear.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);

      /* leftFront.setChannelMode(DcMotorController.RunMode.RUN_USING_ENCODERS);
        rightFront.setChannelMode(DcMotorController.RunMode.RUN_USING_ENCODERS);
        leftRear.setChannelMode(DcMotorController.RunMode.RUN_USING_ENCODERS);
        rightRear.setChannelMode(DcMotorController.RunMode.RUN_USING_ENCODERS);*/

        leftFront.setChannelMode(DcMotorController.RunMode.RUN_TO_POSITION);
        rightFront.setChannelMode(DcMotorController.RunMode.RUN_TO_POSITION);
        // leftRear.setChannelMode(DcMotorController.RunMode.RUN_TO_POSITION);
        // rightRear.setChannelMode(DcMotorController.RunMode.RUN_TO_POSITION);

        // Update the current devMode
        devMode_a = dc_1.getMotorControllerDeviceMode();
        devMode_b = dc_2.getMotorControllerDeviceMode();

        // double dist=distx;
        // double power=powerx;
        // telemetry.addData("pre exec", "pre_exec");
        // executeMoveEncoder(dist, power);
        // telemetry.addData("post exec","post_exec");

        // ii = ii + 1;
        double cnt_target = cnts_distin * dist;
        telemetry.addData("cnt_target", (int) cnt_target);
        // telemetry.addData("ii", ii);
        leftFront.setTargetPosition((int) cnt_target);
        rightFront.setTargetPosition((int) cnt_target);
        // leftRear.setTargetPosition((int) cnt_target);
        // rightRear.setTargetPosition((int) cnt_target);

        // telemetry.addData("left device mode", devMode_a);
        // telemetry.addData("right device mode", devMode_b);

        leftFront.setPower(power);
        rightFront.setPower(power);
        leftRear.setPower(power);
        rightRear.setPower(power);

        wait1Msec(20);

        dc_1.setMotorControllerDeviceMode(DcMotorController.DeviceMode.READ_ONLY);
        dc_2.setMotorControllerDeviceMode(DcMotorController.DeviceMode.READ_ONLY);

        while (rightFrontCurrentEncoder < cnt_target && leftFrontCurrentEncoder < cnt_target) {
            // If we've switched to read mode, we can read data from the NXT device.
            // Only necessary on NXT devices.

                // Update the reads after some loops, when the command has successfully propagated through.
                telemetry.addData("leftFront Power", leftFront.getPower());
                telemetry.addData("rightFront power", rightFront.getPower());
                telemetry.addData("leftRear Power", leftRear.getPower());
                telemetry.addData("rightRear power", rightRear.getPower());

                telemetry.addData("left device mode", devMode_a);
                telemetry.addData("right device mode", devMode_b);

                rightFrontCurrentEncoder = rightFront.getCurrentPosition();
                leftFrontCurrentEncoder = leftFront.getCurrentPosition();
                // rightRearCurrentEncoder = rightRear.getCurrentPosition();
                // leftRearCurrentEncoder = leftRear.getCurrentPosition();

                telemetry.addData("right front curr enc", rightFrontCurrentEncoder);
                telemetry.addData("left front curr enc", leftFrontCurrentEncoder);
                // telemetry.addData("right rear curr enc", rightRearCurrentEncoder);
                // telemetry.addData("left rear curr enc", leftRearCurrentEncoder);

                // leftFrontTargetEncoder = leftFront.getTargetPosition();
                // rightFrontTargetEncoder = rightFront.getTargetPosition();
                // leftRearTargetEncoder = leftRear.getTargetPosition();
                // rightRearTargetEncoder = rightRear.getTargetPosition();

                // telemetry.addData("right front target", rightFrontTargetEncoder);
                // telemetry.addData("left front target", leftFrontTargetEncoder);
                // telemetry.addData("right rear target", rightRearTargetEncoder);
                // telemetry.addData("left rear target", leftRearTargetEncoder);

                // Only needed on Nxt devices, but not on USB devices

                // Reset the loop
                // numOpLoops = 0;

            // Update the current devMode
            // devMode_a = dc_1.getMotorControllerDeviceMode();
            // devMode_b = dc_2.getMotorControllerDeviceMode();
            // numOpLoops++;


        }

        dc_1.setMotorControllerDeviceMode(DcMotorController.DeviceMode.WRITE_ONLY);
        dc_2.setMotorControllerDeviceMode(DcMotorController.DeviceMode.WRITE_ONLY);
        telemetry.addData("inside loop", "yes");
        leftFront.setPower(0.0);
        rightFront.setPower(0.0);
        rightRear.setPower(0.0);
        leftRear.setPower(0.0);
    }

    void wait1Msec (long time) throws InterruptedException {
        //tc: added sleep function so it waits
        sleep(time);
        return;
    }

    private boolean withinMarginOfError(int goal, int value) {
        int lowerMargin = goal - 5;
        int upperMargin = goal + 5;
        return (value >= lowerMargin && value <= upperMargin);
    }

}