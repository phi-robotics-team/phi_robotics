package com.qualcomm.ftcrobotcontroller.opmodes;

import com.qualcomm.robotcore.eventloop.opmode.OpMode;
import com.qualcomm.robotcore.hardware.DcMotor;
import com.qualcomm.robotcore.hardware.Servo;
import com.qualcomm.robotcore.util.Range;

public class TeleOp extends OpMode {

    final double LEFT_SERVO_START = 1.0;
    final double LEFT_SERVO_EXTENDED =  0.5;
    final double RIGHT_SERVO_START = 0.0;
    final double RIGHT_SERVO_EXTENDED = 0.5;
    final double HOOK_START =  0.0;
    final double HOOK_EXTENDED = 1.0;
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
    Servo servo1;
    Servo servo2;
    DcMotor sliderMotor;
    boolean rightActive;
    boolean leftActive;
    DcMotor wenchMotor;
    DcMotor motorArm;
    DcMotor flapperMotor;
    Servo servo3;
    Servo servo4;
    boolean hookActive;
    boolean linkActive;
    boolean flapperActive;
    boolean grappleActive;

    @Override
    public void init() {
        //Get references to the motors and servos from the hardware map
        servo1 = hardwareMap.servo.get("leftSide");
        servo2 = hardwareMap.servo.get("rightSide");
        sliderMotor = hardwareMap.dcMotor.get("slider");
        wenchMotor = hardwareMap.dcMotor.get("wench");
        leftMotor = hardwareMap.dcMotor.get("left_drive");
        rightMotor = hardwareMap.dcMotor.get("right_drive");
        servo3 = hardwareMap.servo.get("hook");
        motorArm = hardwareMap.dcMotor.get("t_rex_arm");
        servo4 = hardwareMap.servo.get("trapDoor");
        flapperMotor = hardwareMap.dcMotor.get("flappers");
        //Reverse the right motor
        rightMotor.setDirection(DcMotor.Direction.REVERSE);
        // This code tracks the state of the servos as active or inactive
        rightActive = false;
        leftActive = false;
        hookActive = false;
        linkActive = false;
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
        float yValue = gamepad1.left_stick_y;

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
        if (gamepad1.a) {
            if (leftActive == false) {
               servo1.setPosition(LEFT_SERVO_START);
                leftActive = true;
            } else if (leftActive == true){
                servo1.setPosition(LEFT_SERVO_EXTENDED);
                leftActive = false;
            }
        }

        // Use B button to open and close right arm
        if (gamepad1.b) {
            if (rightActive == false) {
                servo2.setPosition(RIGHT_SERVO_START);
                rightActive = true;
            } else if (rightActive == true){
                servo2.setPosition(RIGHT_SERVO_EXTENDED);
                rightActive = false;
            }
        }

        // Use X button to extend and retract hook
        if (gamepad1.x) {
            if (hookActive == false) {
                servo3.setPosition(HOOK_START);
                hookActive = true;
            } else if (hookActive == true){
                servo3.setPosition(HOOK_EXTENDED);
                hookActive = false;
            }
        }

        if(gamepad1.y) {
            servo4.setPosition(TRAP_DOOR_START);
        } else {
            servo4.setPosition(TRAP_DOOR_EXTENDED);
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

