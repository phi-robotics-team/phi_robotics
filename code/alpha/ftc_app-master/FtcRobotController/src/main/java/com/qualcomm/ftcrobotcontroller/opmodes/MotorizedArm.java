package com.qualcomm.ftcrobotcontroller.opmodes;

import com.qualcomm.robotcore.eventloop.opmode.OpMode;
import com.qualcomm.robotcore.hardware.DcMotor;
import com.qualcomm.robotcore.util.Range;

public class MotorizedArm extends OpMode {

    DcMotor leftMotor;
    DcMotor rightMotor;
    DcMotor leftArm;

    @Override
    public void init() {
        //Get references to the motors and servos from the hardware map
        leftArm = hardwareMap.dcMotor.get("left_arm");
        leftMotor = hardwareMap.dcMotor.get("left_drive");
        rightMotor = hardwareMap.dcMotor.get("right_drive");
        //Reverse the right motor
        rightMotor.setDirection(DcMotor.Direction.REVERSE);
    }

    @Override
    public void loop() {

        //Get the values from the gamepads
        //Note: pushing the stick all the way up returns -1,
        // so we need to reverse the y values
        float xValue = gamepad1.left_stick_x;
        float yValue = -gamepad1.left_stick_y;

        //Calculate the power needed for each motor
        float leftPower = yValue + xValue;
        float rightPower = yValue - xValue;

        //Clip the power values so that it only goes from -1 to 1
        leftPower = Range.clip(leftPower, -1, 1);
        rightPower = Range.clip(rightPower, -1, 1);

        //Set the power of the motors with the gamepad values
        leftMotor.setPower(leftPower);
        rightMotor.setPower(rightPower);

        // This code will control the up and down movement of
        // the arm using the y and b gamepad buttons.
        if(gamepad1.a) {
            leftArm.setPower(0.1);
        }
        else if(gamepad1.b) {
            leftArm.setPower(-0.1);
        }
        else {
            leftArm.setPower(0);
        }


    }

}

