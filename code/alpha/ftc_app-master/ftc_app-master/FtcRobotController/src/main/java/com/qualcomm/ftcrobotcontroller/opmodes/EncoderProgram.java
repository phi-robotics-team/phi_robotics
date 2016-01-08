package com.qualcomm.ftcrobotcontroller.opmodes;

import com.qualcomm.robotcore.eventloop.opmode.LinearOpMode;
import com.qualcomm.robotcore.eventloop.opmode.OpMode;
import com.qualcomm.robotcore.hardware.DcMotor;
import com.qualcomm.robotcore.hardware.DcMotorController;


/**
 * Created by phiro on 9/17/2015.
 */
public class EncoderProgram extends OpMode {


        DcMotor rightMotor;
        DcMotor leftMotor;

        final static int ENCODER_CPR = 1120;     //Encoder Counts per Revolution
        final static double GEAR_RATIO = 1;      //Gear Ratio
        final static int WHEEL_DIAMETER = 3;     //Diameter of the wheel in inches
        final static int DISTANCE = 24;          //Distance in inches to drive

        final static double CIRCUMFERENCE = Math.PI * WHEEL_DIAMETER;
        final static double ROTATIONS = DISTANCE / CIRCUMFERENCE;
        final static double COUNTS = ENCODER_CPR * ROTATIONS * GEAR_RATIO;

        @Override
        public void init() {
            leftMotor = hardwareMap.dcMotor.get("left_drive");
            rightMotor = hardwareMap.dcMotor.get("right_drive");

            rightMotor.setDirection(DcMotor.Direction.REVERSE);

            leftMotor.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);
            rightMotor.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);
        }

        @Override
        public void start() {
            leftMotor.setTargetPosition((int) COUNTS);
            rightMotor.setTargetPosition((int) COUNTS);

            leftMotor.setChannelMode(DcMotorController.RunMode.RUN_TO_POSITION);
            rightMotor.setChannelMode(DcMotorController.RunMode.RUN_TO_POSITION);

            leftMotor.setPower(0.5);
            rightMotor.setPower(0.5);
        }

        @Override
        public void loop() {
            telemetry.addData("Motor Target", COUNTS);
            telemetry.addData("Left Position", leftMotor.getCurrentPosition());
            telemetry.addData("Right Position", rightMotor.getCurrentPosition());
        }


    }
