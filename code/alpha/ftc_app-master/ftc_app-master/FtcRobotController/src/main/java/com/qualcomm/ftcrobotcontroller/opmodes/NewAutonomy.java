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
    final static int DISTANCE = 60;          //Distance in inches to drive
    final static int AFTER_TURN = 40;




    final static double CIRCUMFERENCE = Math.PI * WHEEL_DIAMETER;
    final static double FORWARD = DISTANCE / CIRCUMFERENCE;
    final static double FIRST = ENCODER_CPR * FORWARD * GEAR_RATIO;
    final static double AGAIN = AFTER_TURN / CIRCUMFERENCE;
    final static double SECOND = ENCODER_CPR * AGAIN * GEAR_RATIO;



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

        leftDrive.setTargetPosition((int) FIRST);
        rightDrive.setTargetPosition((int) FIRST);

        leftDrive.setChannelMode(DcMotorController.RunMode.RUN_TO_POSITION);
        rightDrive.setChannelMode(DcMotorController.RunMode.RUN_TO_POSITION);

        leftDrive.setPower(0.5);
        rightDrive.setPower(0.5);

        leftDrive.setChannelMode(DcMotorController.RunMode.RUN_WITHOUT_ENCODERS);
        rightDrive.setChannelMode(DcMotorController.RunMode.RUN_WITHOUT_ENCODERS);

        leftDrive.setPower(0.5);
        rightDrive.setPower(-0.5);

        sleep(2000);

        leftDrive.setChannelMode(DcMotorController.RunMode.RUN_USING_ENCODERS);
        rightDrive.setChannelMode(DcMotorController.RunMode.RUN_USING_ENCODERS);


        leftDrive.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);
        rightDrive.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);

        leftDrive.setTargetPosition((int) SECOND);
        rightDrive.setTargetPosition((int) SECOND);

        leftDrive.setChannelMode(DcMotorController.RunMode.RUN_TO_POSITION);
        rightDrive.setChannelMode(DcMotorController.RunMode.RUN_TO_POSITION);

        leftDrive.setPower(0.5);
        rightDrive.setPower(0.5);

    }

}


