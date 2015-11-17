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
    DcMotor sliderMotor;
    boolean rightActive;
    boolean leftActive;
    DcMotor wenchMotor;

    @Override
    public void init() {
        //Get references to the motors and servos from the hardware map
        servo1 = hardwareMap.servo.get("servo_1");
        servo2 = hardwareMap.servo.get("servo_2");
        sliderMotor = hardwareMap.dcMotor.get("slider");
        wenchMotor = hardwareMap.dcMotor.get("wench");
        leftMotor = hardwareMap.dcMotor.get("left_drive");
        rightMotor = hardwareMap.dcMotor.get("right_drive");
        //Reverse the right motor
        rightMotor.setDirection(DcMotor.Direction.REVERSE);
        // This code tracks the state of the servos as active or inactive
        rightActive = false;
        leftActive = false;

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
        // the grapple hook using the right joystick
        float grapple = gamepad1.right_stick_y;
        grapple = Range.clip(grapple, -1, 1);
        wenchMotor.setPower(grapple);

        // The left servo will be using the button A to move
        if (gamepad1.a && leftActive == false) {
            servo1.setPosition(LEFT_OPEN_POSITION);
            leftActive = true;
        } else if (gamepad1.a && leftActive == true) {
            servo1.setPosition(LEFT_CLOSED_POSITION);
            leftActive = false;
        }
        // The right servo will be using button X to move
        if (gamepad1.b && rightActive == false) {
            servo1.setPosition(RIGHT_OPEN_POSITION);
            rightActive = true;
        } else if (gamepad1.b && rightActive == true) {
            servo1.setPosition(RIGHT_CLOSED_POSITION);
            rightActive = false;
        }

        float sliderUp = gamepad1.right_trigger;
        float sliderDown = gamepad1.left_trigger;
        float slider = sliderUp - sliderDown;
        slider = Range.clip(slider, -1, 1);
        sliderMotor.setPower(slider);

    }

}

