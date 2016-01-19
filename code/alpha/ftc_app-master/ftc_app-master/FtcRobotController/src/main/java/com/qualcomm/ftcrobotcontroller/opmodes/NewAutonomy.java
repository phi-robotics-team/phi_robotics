package com.qualcomm.ftcrobotcontroller.opmodes;

import com.qualcomm.robotcore.eventloop.opmode.LinearOpMode;
import com.qualcomm.robotcore.eventloop.opmode.OpMode;
import com.qualcomm.robotcore.hardware.DcMotor;
import com.qualcomm.robotcore.hardware.DcMotorController;

/**
 * Created by phiro on 1/11/2016.
 */
public class NewAutonomy extends LinearOpMode {


    DcMotor leftDrive;
    DcMotor rightDrive;

    final static int ENCODER_CPR = 1120;     //Encoder Counts per Revolution
    final static double GEAR_RATIO = 16.24;  //Gear Ratio
    final static double WHEEL_DIAMETER = 2.5;     //Diameter of the wheel in inches
    final static int DISTANCE = 40;          //Distance in inches to drive forwards




    final static double CIRCUMFERENCE = Math.PI * WHEEL_DIAMETER;
    final static double FORWARD = DISTANCE / CIRCUMFERENCE;
    final static double DRIVE = ENCODER_CPR * FORWARD * GEAR_RATIO;



    @Override
    public void runOpMode() throws InterruptedException {
        //setup the left and right motors from the configuration file
        leftDrive = hardwareMap.dcMotor.get("leftDrive");
        rightDrive = hardwareMap.dcMotor.get("rightDrive");
        //reverse the right side motor
        leftDrive.setDirection(DcMotor.Direction.REVERSE);

        waitForStart();

        leftDrive.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);
        rightDrive.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);

        leftDrive.setTargetPosition((int) DRIVE);
        rightDrive.setTargetPosition((int) DRIVE);

        leftDrive.setChannelMode(DcMotorController.RunMode.RUN_TO_POSITION);
        rightDrive.setChannelMode(DcMotorController.RunMode.RUN_TO_POSITION);

        leftDrive.setPower(0.5);
        rightDrive.setPower(0.5);

        leftDrive.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);
        rightDrive.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);

        leftDrive.setTargetPosition((int) DRIVE);
        rightDrive.setTargetPosition((int) -DRIVE);

        leftDrive.setChannelMode(DcMotorController.RunMode.RUN_TO_POSITION);
        rightDrive.setChannelMode(DcMotorController.RunMode.RUN_TO_POSITION);

        leftDrive.setPower(0.5);
        rightDrive.setPower(0.5);

        leftDrive.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);
        rightDrive.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);

        leftDrive.setTargetPosition((int) DRIVE);
        rightDrive.setTargetPosition((int) DRIVE);

        leftDrive.setChannelMode(DcMotorController.RunMode.RUN_TO_POSITION);
        rightDrive.setChannelMode(DcMotorController.RunMode.RUN_TO_POSITION);

        leftDrive.setPower(0.5);
        rightDrive.setPower(0.5);

    }

}


