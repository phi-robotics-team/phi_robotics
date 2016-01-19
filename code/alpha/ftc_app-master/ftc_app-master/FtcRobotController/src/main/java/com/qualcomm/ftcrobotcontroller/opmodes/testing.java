package com.qualcomm.ftcrobotcontroller.opmodes;

import com.qualcomm.robotcore.eventloop.opmode.LinearOpMode;
import com.qualcomm.robotcore.hardware.DcMotor;
import com.qualcomm.robotcore.hardware.DcMotorController;

/**
 * Created by phi on 11/19/2015.
 */

public class testing extends LinearOpMode {

    DcMotor leftDrive;
    DcMotor rightDrive;
    DcMotorController dc_1;
    DcMotorController.DeviceMode devMode_a;

    int rotDirection;
    int state=0;

    // wheel and motor info to calculate the # of counts on encoder per inch of distance 'cnts_distin'
    double diam = 2.5;
    //long cnts_motorrev = 1440;
    long cnts_motorrev = 1120;
    double dist_wheelrev = 3.1416 * diam;
    double motorrev_wheelrev = 1.0;
    double cnts_distin = cnts_motorrev * motorrev_wheelrev / dist_wheelrev;


    @Override
    public void runOpMode() throws InterruptedException {
        leftDrive = hardwareMap.dcMotor.get("leftDrive");
        rightDrive = hardwareMap.dcMotor.get("rightDrive");
        dc_1 = hardwareMap.dcMotorController.get("dc_1");

        rightDrive.setDirection(DcMotor.Direction.REVERSE);


        // wait for the start button to be pressed.
        waitForStart();

        double reqTurnDegrees;
        double power;
        double negativePower;
        double dist;

        leftDrive.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);
        rightDrive.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);
        //leftFront.setChannelMode(DcMotorController.RunMode.RUN_TO_POSITION);
        //rightFront.setChannelMode(DcMotorController.RunMode.RUN_TO_POSITION);
        telemetry.addData("dc_runmode", dc_1.getMotorControllerDeviceMode());

        //time.startTime();
        while (opModeIsActive()) {
            switch (state) {
                case 0:

                    devMode_a = DcMotorController.DeviceMode.WRITE_ONLY;
                    dist = 40.0;
                    power = 1.0;
                    MoveEncoder(dist, power);
                    //  leftFront.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);
                    //  rightFront.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);
                    state= state + 1;
                    telemetry.addData("state", state);
                    wait1Msec(200);
                case 1:
                    devMode_a = DcMotorController.DeviceMode.WRITE_ONLY;
                    dist = 10.0;
                    power = 0.5;
                    negativePower = -0.5;
                    TurnEncoder(dist, power,negativePower,true);
                    state = state + 1;
                    telemetry.addData("state", state);
                    wait1Msec(200);

                case 2:
                    devMode_a = DcMotorController.DeviceMode.WRITE_ONLY;
                    dist = 40.0;
                    power = 1.0;
                    MoveEncoder(dist, power);
                    //  leftFront.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);
                    //  rightFront.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);
                    state= state + 1;
                    telemetry.addData("state", state);
                    wait1Msec(200);
                //case 3:
                    //devMode_a = DcMotorController.DeviceMode.WRITE_ONLY;
                    //dist = 10.0;
                    //power = 0.5;
                    //negativePower = -0.5;
                    //TurnEncoder(dist, power,negativePower,true);
                    //state = state + 1;
                    //telemetry.addData("state", state);
                    //wait1Msec(200);


                    //case 4:
                    //devMode_a = DcMotorController.DeviceMode.WRITE_ONLY;
                    //devMode_b = DcMotorController.DeviceMode.WRITE_ONLY;
                    //dist = 5.0;
                    // power = 1.0;
                    //MoveEncoder(dist, power);
                    //  leftFront.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);
                    //  rightFront.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);
                    //state= state + 1;
                    //telemetry.addData("state", state);
                    //wait1Msec(200);
                default:
                    telemetry.addData("default","default");
                    wait1Msec(5000);
            }

            waitOneFullHardwareCycle();

        }
    }

    void MoveEncoder (double dist, double power) throws InterruptedException {
        double leftFrontCurrentEncoder=0;
        double rightFrontCurrentEncoder=0;
        leftDrive.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);
        rightDrive.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);
        wait1Msec(20);
        leftDrive.setChannelMode(DcMotorController.RunMode.RUN_USING_ENCODERS);
        rightDrive.setChannelMode(DcMotorController.RunMode.RUN_USING_ENCODERS);
        wait1Msec(20);
        leftDrive.setChannelMode(DcMotorController.RunMode.RUN_TO_POSITION);
        rightDrive.setChannelMode(DcMotorController.RunMode.RUN_TO_POSITION);
        wait1Msec(20);

        devMode_a = dc_1.getMotorControllerDeviceMode();
        wait1Msec(20);

        double cnt_target = cnts_distin * dist;
        telemetry.addData("cnt_target", (int) cnt_target);
        // telemetry.addData("ii", ii);
        leftDrive.setTargetPosition((int) cnt_target);
        rightDrive.setTargetPosition((int) cnt_target);
        // leftRear.setTargetPosition((int) cnt_target);
        // rightRear.setTargetPosition((int) cnt_target);

        telemetry.addData("left device mode", devMode_a);

        leftDrive.setPower(power);
        rightDrive.setPower(power);

        wait1Msec(200);

        dc_1.setMotorControllerDeviceMode(DcMotorController.DeviceMode.READ_ONLY);

        while (rightFrontCurrentEncoder < cnt_target && leftFrontCurrentEncoder < cnt_target) {
            // If we've switched to read mode, we can read data from the NXT device.
            // Only necessary on NXT devices.

            // Update the reads after some loops, when the command has successfully propagated through.
            telemetry.addData("leftFront Power", leftDrive.getPower());
            telemetry.addData("rightFront power", rightDrive.getPower());

            telemetry.addData("left device mode", devMode_a);

            rightFrontCurrentEncoder = leftDrive.getCurrentPosition();
            leftFrontCurrentEncoder = rightDrive.getCurrentPosition();
            // rightRearCurrentEncoder = rightRear.getCurrentPosition();
            // leftRearCurrentEncoder = leftRear.getCurrentPosition();

            telemetry.addData("right front curr enc", rightFrontCurrentEncoder);
            telemetry.addData("left front curr enc", leftFrontCurrentEncoder);



            // Only needed on Nxt devices, but not on USB devices



        }

        dc_1.setMotorControllerDeviceMode(DcMotorController.DeviceMode.WRITE_ONLY);
        wait1Msec(20);
        telemetry.addData("inside loop", "yes");
        leftDrive.setPower(0.0);
        rightDrive.setPower(0.0);

        leftDrive.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);
        rightDrive.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);
        leftDrive.setChannelMode(DcMotorController.RunMode.RUN_WITHOUT_ENCODERS);
        rightDrive.setChannelMode(DcMotorController.RunMode.RUN_WITHOUT_ENCODERS);
    }

    void TurnEncoder (double dist, double power, double negativePower, boolean rightTurn) throws InterruptedException {
        double leftFrontCurrentEncoder = 0;
        double rightFrontCurrentEncoder = 0;
        leftDrive.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);
        rightDrive.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);
        wait1Msec(20);
        leftDrive.setChannelMode(DcMotorController.RunMode.RUN_USING_ENCODERS);
        rightDrive.setChannelMode(DcMotorController.RunMode.RUN_USING_ENCODERS);
        wait1Msec(20);
        leftDrive.setChannelMode(DcMotorController.RunMode.RUN_TO_POSITION);
        rightDrive.setChannelMode(DcMotorController.RunMode.RUN_TO_POSITION);
        wait1Msec(20);

        devMode_a = dc_1.getMotorControllerDeviceMode();
        wait1Msec(20);

        double cnt_target = cnts_distin * dist;
        telemetry.addData("cnt_target", (int) cnt_target);
        // telemetry.addData("ii", ii);
        leftDrive.setTargetPosition((int) cnt_target);
        rightDrive.setTargetPosition((int) cnt_target);
        // leftRear.setTargetPosition((int) cnt_target);
        // rightRear.setTargetPosition((int) cnt_target);

        telemetry.addData("left device mode", devMode_a);
        if (rightTurn) {
            leftDrive.setPower(power);
            rightDrive.setPower(negativePower);
        } else {
            leftDrive.setPower(negativePower);
            rightDrive.setPower(power);
        }

        wait1Msec(200);

        dc_1.setMotorControllerDeviceMode(DcMotorController.DeviceMode.READ_ONLY);

        while (rightFrontCurrentEncoder < cnt_target && leftFrontCurrentEncoder < cnt_target) {
            // If we've switched to read mode, we can read data from the NXT device.
            // Only necessary on NXT devices.

            // Update the reads after some loops, when the command has successfully propagated through.
            telemetry.addData("leftFront Power", leftDrive.getPower());
            telemetry.addData("rightFront power", rightDrive.getPower());

            telemetry.addData("left device mode", devMode_a);

            rightFrontCurrentEncoder = leftDrive.getCurrentPosition();
            leftFrontCurrentEncoder = rightDrive.getCurrentPosition();
            // rightRearCurrentEncoder = rightRear.getCurrentPosition();
            // leftRearCurrentEncoder = leftRear.getCurrentPosition();

            telemetry.addData("right front curr enc", rightFrontCurrentEncoder);
            telemetry.addData("left front curr enc", leftFrontCurrentEncoder);


            // Only needed on Nxt devices, but not on USB devices


        }

        dc_1.setMotorControllerDeviceMode(DcMotorController.DeviceMode.WRITE_ONLY);
        wait1Msec(20);
        telemetry.addData("inside loop", "yes");
        leftDrive.setPower(0.0);
        rightDrive.setPower(0.0);

        leftDrive.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);
        rightDrive.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);
        leftDrive.setChannelMode(DcMotorController.RunMode.RUN_WITHOUT_ENCODERS);
        rightDrive.setChannelMode(DcMotorController.RunMode.RUN_WITHOUT_ENCODERS);
    }
    //Waits 1t milliseconds
    void wait1Msec(long time) throws InterruptedException {
        Thread.sleep(time);
        return;
    }
}