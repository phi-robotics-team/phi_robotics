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
    final static double GEAR_RATIO = 16.24;      //Gear Ratio
    final static int WHEEL_DIAMETER = 3;     //Diameter of the wheel in inches
    final static int DISTANCE = 24;          //Distance in inches to drive

    final static double CIRCUMFERENCE = Math.PI * WHEEL_DIAMETER;
    final static double ROTATIONS = DISTANCE / CIRCUMFERENCE;
    final static double COUNTS = ENCODER_CPR * ROTATIONS * GEAR_RATIO;



    @Override
    public void runOpMode() throws InterruptedException {
        //setup the left and right motors from the configuration file
        leftDrive = hardwareMap.dcMotor.get("left_drive");
        rightDrive = hardwareMap.dcMotor.get("right_drive");
        //reverse the right side motor
        rightDrive.setDirection(DcMotor.Direction.REVERSE);

        leftDrive.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);
        rightDrive.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);

        waitForStart();

        leftDrive.setTargetPosition((int) COUNTS);
        rightDrive.setTargetPosition((int) COUNTS);

        leftDrive.setChannelMode(DcMotorController.RunMode.RUN_TO_POSITION);
        rightDrive.setChannelMode(DcMotorController.RunMode.RUN_TO_POSITION);

        leftDrive.setPower(0.5);
        rightDrive.setPower(0.5);


    }

}


