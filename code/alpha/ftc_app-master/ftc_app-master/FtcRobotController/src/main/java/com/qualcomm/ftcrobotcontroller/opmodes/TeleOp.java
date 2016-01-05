package com.qualcomm.ftcrobotcontroller.opmodes;

import com.qualcomm.robotcore.eventloop.opmode.OpMode;
import com.qualcomm.robotcore.hardware.DcMotor;
import com.qualcomm.robotcore.hardware.Servo;
import com.qualcomm.robotcore.util.Range;

public class TeleOp extends OpMode {


    final double TRAP_DOOR_START = 0.0;
    final double TRAP_DOOR_EXTENDED = 1.0;

    final double WENCH_POWER_START = 0.0;
    final double WENCH_POWER_EXTENDED = 1.0;
    final double WENCH_POWER_RETRACTED = -1.0;
    final double FLAPPER_POWER_START = 0.0;
    final double FLAPPER_POWER_FORWARD = 0.8;
    final double FLAPPER_POWER_REVERSE = -0.8;

    DcMotor leftMotor;
    DcMotor rightMotor;
    DcMotor sliderMotor;
    DcMotor wenchMotor;
    DcMotor motorArm;
    DcMotor flapperMotor;
    Servo servo1;
    Servo servo2;
    boolean flapperActive;
    boolean grappleActive;

    @Override
    public void init() {
        //Get references to the motors and servos from the hardware map
        sliderMotor = hardwareMap.dcMotor.get("slider");
        wenchMotor = hardwareMap.dcMotor.get("wench");
        leftMotor = hardwareMap.dcMotor.get("left_drive");
        rightMotor = hardwareMap.dcMotor.get("right_drive");
        servo1 = hardwareMap.servo.get("hook");
        motorArm = hardwareMap.dcMotor.get("t_rex_arm");
        servo2 = hardwareMap.servo.get("trapDoor");
        flapperMotor = hardwareMap.dcMotor.get("flappers");
        //Reverse the right motor
        rightMotor.setDirection(DcMotor.Direction.REVERSE);
        motorArm.setDirection(DcMotor.Direction.REVERSE);
        // This code tracks the state of the servos as active or inactive
        flapperActive = false;
        grappleActive = false;

        // Initialize the servo and delta position for left servo
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

        float armPosition = gamepad1.right_stick_y;
        float arm = Range.clip(armPosition, -1, 1);
        motorArm.setPower(arm);

        // Use A button to open and close left arm
        if(gamepad1.a) {
            servo1.setPosition(0.0);
        }


        if(gamepad1.b) {
            servo1.setPosition(1.0);
        }

        if(gamepad1.y) {
            servo2.setPosition(TRAP_DOOR_START);
        } else {
            servo2.setPosition(TRAP_DOOR_EXTENDED);
        }

        if (gamepad1.left_bumper) {
            if (flapperActive == false) {
                flapperMotor.setPower(FLAPPER_POWER_START);
                flapperActive = true;
            } else if (flapperActive == true){
               flapperMotor.setPower(FLAPPER_POWER_FORWARD);
                flapperActive = false;
            }
        }
        if (gamepad1.right_bumper) {
            if (flapperActive == false) {
                flapperMotor.setPower(FLAPPER_POWER_START);
                flapperActive = true;
            } else if (flapperActive == true){
                flapperMotor.setPower(FLAPPER_POWER_REVERSE);
                flapperActive = false;
            }
        }
        if (gamepad1.dpad_up) {
            if (grappleActive == false) {
                wenchMotor.setPower(WENCH_POWER_START);
                grappleActive = true;
            } else if (grappleActive == true){
                wenchMotor.setPower(WENCH_POWER_EXTENDED);
                grappleActive = false;
            }
        }
        if (gamepad1.dpad_down) {
            if (grappleActive == false) {
                wenchMotor.setPower(WENCH_POWER_START);
                grappleActive = true;
            } else if (grappleActive == true){
                wenchMotor.setPower(WENCH_POWER_RETRACTED);
                grappleActive = false;
            }
        }

            // Slider controls and positioning
        float sliderUp = gamepad1.right_trigger;
        float sliderDown = gamepad1.left_trigger;
        float slider = sliderUp - sliderDown;
        slider = Range.clip(slider, -1, 1);
        sliderMotor.setPower(slider);

    }
}

