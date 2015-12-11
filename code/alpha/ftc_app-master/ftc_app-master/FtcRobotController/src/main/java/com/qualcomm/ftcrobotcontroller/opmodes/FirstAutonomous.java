package com.qualcomm.ftcrobotcontroller.opmodes;

import com.qualcomm.robotcore.eventloop.opmode.LinearOpMode;
import com.qualcomm.robotcore.hardware.DcMotor;

/**
 * Created by phiro on 9/17/2015.
 */
public class FirstAutonomous extends LinearOpMode {

        DcMotor leftMotor;
        DcMotor rightMotor;

        @Override
        public void runOpMode() throws InterruptedException {



            leftMotor = hardwareMap.dcMotor.get("left_drive");
            rightMotor = hardwareMap.dcMotor.get("right_drive");
            //reverse the right side motor
            rightMotor.setDirection(DcMotor.Direction.REVERSE);


            waitForStart();


            leftMotor.setPower(0.5);
            rightMotor.setPower(0.5);


            sleep(2000);


            leftMotor.setPower(0);
            rightMotor.setPower(0);
        }
    }

