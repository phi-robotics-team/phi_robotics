package com.qualcomm.ftcrobotcontroller.opmodes;

import android.os.SystemClock;
import com.qualcomm.robotcore.eventloop.opmode.LinearOpMode;
import com.qualcomm.robotcore.eventloop.opmode.OpMode;
import com.qualcomm.robotcore.hardware.DcMotor;
import com.qualcomm.robotcore.hardware.DcMotorController;

/**
 * Created by phi on 10/15/2015.
 */
public class encoderDrive extends LinearOpMode {

    DcMotor leftFront;
    DcMotor leftRear;
    DcMotor rightFront;
    DcMotor rightRear;
    DcMotorController dc_1;
    DcMotorController dc_2;

    final static int ENCODER_CPR = 1120;  // Encoder counts per revolution
    final static double GEAR_RATIO = 0.3;   // Gear ratio
    final static int WHEEL_DIAMETER = 4;  // Diameter of the wheel in inches
    final static int DISTANCE = 6;  // Distance in inches to drive

    final static double CIRCUMFERENCE = Math.PI * WHEEL_DIAMETER;
    final static double ROTATION = DISTANCE / CIRCUMFERENCE;
    final static double COUNTS = ENCODER_CPR * ROTATION * GEAR_RATIO;

/*    public encoderDrive() {

    }*/


    // @Override
    //public void init() {


//    }

/*    @Override
    public void start() {
        leftFront.setTargetPosition((int) COUNTS);
        rightFront.setTargetPosition((int) COUNTS);
        leftRear.setTargetPosition((int) COUNTS);
        rightRear.setTargetPosition((int) COUNTS);

        leftFront.setChannelMode(DcMotorController.RunMode.RUN_TO_POSITION);
        rightFront.setChannelMode(DcMotorController.RunMode.RUN_TO_POSITION);
        leftRear.setChannelMode(DcMotorController.RunMode.RUN_TO_POSITION);
        rightRear.setChannelMode(DcMotorController.RunMode.RUN_TO_POSITION);

        leftFront.setPower(0.5);
        rightFront.setPower(0.5);
        leftRear.setPower(0.5);
        rightRear.setPower(0.5);


    }*/

    @Override
    public void runOpMode() throws InterruptedException {
        waitForStart();

        leftFront = hardwareMap.dcMotor.get("leftFront");
        rightFront = hardwareMap.dcMotor.get("rightFront");
        leftRear = hardwareMap.dcMotor.get("leftRear");
        rightRear = hardwareMap.dcMotor.get("rightRear");

        dc_1 = hardwareMap.dcMotorController.get("dc_1");
        dc_2 = hardwareMap.dcMotorController.get("dc_2");

        dc_1.setMotorControllerDeviceMode(DcMotorController.DeviceMode.WRITE_ONLY);
        dc_2.setMotorControllerDeviceMode(DcMotorController.DeviceMode.WRITE_ONLY);

        rightFront.setDirection(DcMotor.Direction.REVERSE);
        rightRear.setDirection(DcMotor.Direction.REVERSE);

        leftFront.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);
        rightFront.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);
        leftRear.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);
        rightRear.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);

        leftFront.setTargetPosition((int) COUNTS);
        rightFront.setTargetPosition((int) COUNTS);
        leftRear.setTargetPosition((int) COUNTS);
        rightRear.setTargetPosition((int) COUNTS);

        leftFront.setChannelMode(DcMotorController.RunMode.RUN_TO_POSITION);
        rightFront.setChannelMode(DcMotorController.RunMode.RUN_TO_POSITION);
        leftRear.setChannelMode(DcMotorController.RunMode.RUN_TO_POSITION);
        rightRear.setChannelMode(DcMotorController.RunMode.RUN_TO_POSITION);

        leftFront.setPower(0.5);
        rightFront.setPower(0.5);
        leftRear.setPower(0.5);
        rightRear.setPower(0.5);

        while (opModeIsActive()) {

            // while (leftFront.isBusy() || rightFront.isBusy()) {
            dc_1.setMotorControllerDeviceMode(DcMotorController.DeviceMode.READ_ONLY);
            dc_2.setMotorControllerDeviceMode(DcMotorController.DeviceMode.READ_ONLY);
            telemetry.addData("leftMotor", leftFront.getCurrentPosition());
            telemetry.addData("rightMotor", rightFront.getCurrentPosition());
            telemetry.addData("Motor Target", COUNTS);
            waitOneFullHardwareCycle();
            // }
        }
        // telemetry.addData("Motor Target", COUNTS);
        // telemetry.addData("Left Front Position", leftFront.getCurrentPosition());
        // telemetry.addData("right Front Position", rightFront.getCurrentPosition());
    }
}
