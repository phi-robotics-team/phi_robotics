package com.qualcomm.ftcrobotcontroller.opmodes;

import com.qualcomm.robotcore.eventloop.opmode.OpMode;
import com.qualcomm.robotcore.hardware.DcMotor;
import com.qualcomm.robotcore.hardware.Servo;
import com.qualcomm.robotcore.util.Range;

/**
 * Created by phiro on 1/5/2016.
 */
public class NewTeleOp extends OpMode {

    final double TRAP_DOOR_START = 0.0;
    final double TRAP_DOOR_EXTENDED = 1.0;
    final double WHIP_EXTENDED = 1.0;
    final double WHIP_CLOSE = 0.0;

    final double WHEELS_POWER_START = 0.0;
    final double WHEELS_POWER_FORWARD = 0.8;
    final double WHEELS_POWER_REVERSE = -0.8;
    final double WINCH_POWER_START = 0.0;
    final double WINCH_POWER_FORWARD = 0.8;
    final double WINCH_POWER_REVERSE = -0.8;


    DcMotor leftDrive;
    DcMotor rightDrive;
    DcMotor motorArm;
    DcMotor flapperMotor;
    DcMotor wheels;
    DcMotor winchMotor;
    Servo whip;
    Servo trapDoor;
    boolean wheelsActive;
    boolean winchActive;

    @Override
    public void init() {
        //Get references to the motors and servos from the hardware map
        winchMotor = hardwareMap.dcMotor.get("winch");
        leftDrive = hardwareMap.dcMotor.get("leftDrive");
        rightDrive = hardwareMap.dcMotor.get("rightDrive");
        motorArm = hardwareMap.dcMotor.get("t_rex_arm");
        flapperMotor = hardwareMap.dcMotor.get("flappers");
        trapDoor = hardwareMap.servo.get("trapDoor");
        whip = hardwareMap.servo.get("whip");
        //Reverse the right motor
        rightDrive.setDirection(DcMotor.Direction.REVERSE);
        motorArm.setDirection(DcMotor.Direction.REVERSE);

        wheelsActive = false;
        winchActive = false;


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
        leftDrive.setPower(leftPower);
        rightDrive.setPower(rightPower);

        float armPosition = gamepad1.right_stick_y;
        float arm = Range.clip(armPosition, -1, 1);
        motorArm.setPower(arm);

        if (gamepad1.y) {
            trapDoor.setPosition(TRAP_DOOR_START);
        } else {
            trapDoor.setPosition(TRAP_DOOR_EXTENDED);
        }

        if (gamepad1.x){
            whip.setPosition(WHIP_EXTENDED);
        } else {
            whip.setPosition(WHIP_CLOSE);
        }

        if (gamepad1.left_bumper) {
            if (wheelsActive == false) {
                flapperMotor.setPower(WHEELS_POWER_START);
                wheelsActive = true;
            } else if (wheelsActive == true){
                flapperMotor.setPower(WHEELS_POWER_FORWARD);
                wheelsActive = false;
            }
        }
        if (gamepad1.right_bumper) {
            if (wheelsActive == false) {
                wheels.setPower(WHEELS_POWER_START);
                wheelsActive = true;
            } else if (wheelsActive == true) {
                wheels.setPower(WHEELS_POWER_REVERSE);
                wheelsActive = false;
            }
        }
        if (gamepad1.a) {
            if (winchActive == false) {
                winchMotor.setPower(WINCH_POWER_START);
                winchActive = true;
            } else if (winchActive == true){
                winchMotor.setPower(WINCH_POWER_FORWARD);
                winchActive = false;
            }
        }

        if (gamepad1.b) {
            if (winchActive == false) {
                winchMotor.setPower(WINCH_POWER_START);
                winchActive = true;
            } else if (winchActive == true) {
                winchMotor.setPower(WINCH_POWER_REVERSE);
                winchActive = false;
            }
        }

    }
}
