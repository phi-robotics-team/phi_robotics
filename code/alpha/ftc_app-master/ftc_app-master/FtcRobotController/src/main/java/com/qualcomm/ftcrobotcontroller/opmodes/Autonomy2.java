package com.qualcomm.ftcrobotcontroller.opmodes;

import com.qualcomm.robotcore.eventloop.opmode.LinearOpMode;
import com.qualcomm.robotcore.hardware.DcMotor;

public class Autonomy2 extends LinearOpMode{
    DcMotor leftMotor;
    DcMotor rightMotor;

    @Override
    public void runOpMode() throws InterruptedException {
        //setup the left and right motors from the configuration file
        leftMotor = hardwareMap.dcMotor.get("left_drive");
        rightMotor = hardwareMap.dcMotor.get("right_drive");
        //reverse the right side motor
        rightMotor.setDirection(DcMotor.Direction.REVERSE);

        // Wait for the start button to be pressed
        waitForStart();

        // Drive forwards
        leftMotor.setPower(0.5);
        rightMotor.setPower(0.5);

        //Wait for 3 seconds
        sleep(3000);

        // Turn left
        leftMotor.setPower(-0.5);
        rightMotor.setPower(0.5);

        //Wait for 1.2 seconds
        sleep(1200);

        // Drive forwards
        leftMotor.setPower(0.5);
        rightMotor.setPower(0.5);

        // Wait 3.4 seconds
        sleep(3400);


        //Stop the robot
        leftMotor.setPower(0);
        rightMotor.setPower(0);
    }
}


