package com.qualcomm.ftcrobotcontroller.opmodes;

import com.qualcomm.robotcore.eventloop.opmode.OpMode;
import com.qualcomm.robotcore.hardware.DcMotor;
import com.qualcomm.robotcore.hardware.Servo;
import com.qualcomm.robotcore.util.Range;

public class TeleOp extends OpMode {

    final double LEFT_OPEN_POSITION = 0.0;
    final double LEFT_CLOSED_POSITION = 0.5;
    final double RIGHT_OPEN_POSITION = 1.0;
    final double RIGHT_CLOSED_POSITION = 0.5;

    DcMotor leftMotor;
    DcMotor rightMotor;
    Servo servo1;
    Servo servo2;
    DcMotor leftArm;

    @Override
    public void init() {
        //Get references to the motors and servos from the hardware map
        servo1 = hardwareMap.servo.get("servo_1");
        servo2 = hardwareMap.servo.get("servo_2");
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
        float armMove = gamepad1.right_stick_y;

        armMove = Range.clip(armMove, -1, 1);

        leftArm.setPower(armMove);



            //**** Move a Servo with Buttons ****
            //Move servo 1 to the up position when a button is pressed
            if(gamepad1.a) {
                servo1.setPosition(LEFT_OPEN_POSITION);
            }
            //Move servo 1 to the down position when a button is pressed
            if(gamepad1.b) {
                servo1.setPosition(LEFT_CLOSED_POSITION);
            }

            // This code will open and close the gripper with two buttons
        // using 1 button to open and another to close the gripper
        if(gamepad1.x) {
            servo2.setPosition(RIGHT_OPEN_POSITION);
        }
        if(gamepad1.y) {
            servo2.setPosition(RIGHT_CLOSED_POSITION);
        }

    }

}

