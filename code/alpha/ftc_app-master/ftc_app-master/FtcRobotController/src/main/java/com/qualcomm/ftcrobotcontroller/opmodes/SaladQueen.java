package com.qualcomm.ftcrobotcontroller.opmodes;

import com.qualcomm.robotcore.eventloop.opmode.OpMode;
import com.qualcomm.robotcore.hardware.DcMotor;
import com.qualcomm.robotcore.util.Range;

/**
 * Created by phiro on 9/9/2015.
 */
public class SaladQueen extends OpMode {


    DcMotor motorRight;
    DcMotor motorLeft;

    @Override
    public void init() {


        motorRight = hardwareMap.dcMotor.get("motor_2");
        motorLeft = hardwareMap.dcMotor.get("motor_1");
        motorRight.setDirection(DcMotor.Direction.REVERSE);


    }

    @Override
    public void loop() {


        float left_drive = -gamepad1.left_stick_y;
        float right_drive = -gamepad1.right_stick_y;

        left_drive = Range.clip(left_drive, -1, 1);
        right_drive = Range.clip(right_drive, -1, 1);

        motorLeft.setPower(left_drive);
        motorRight.setPower(right_drive);

    }
}


