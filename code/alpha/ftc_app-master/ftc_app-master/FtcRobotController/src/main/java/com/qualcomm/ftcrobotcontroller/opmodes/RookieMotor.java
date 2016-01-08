package com.qualcomm.ftcrobotcontroller.opmodes;

import com.qualcomm.robotcore.eventloop.opmode.OpMode;
import com.qualcomm.robotcore.hardware.DcMotor;
import com.qualcomm.robotcore.hardware.Servo;
import com.qualcomm.robotcore.util.Range;

/**
 * Created by phiro on 1/5/2016.
 */
public class RookieMotor extends OpMode {

    final double TRAP_DOOR_EXTEND = 0.0;
    final double TRAP_DOOR_CLOSE = 1.0;

    DcMotor motorRight;
    DcMotor motorLeft;
    DcMotor motorArm;
    Servo trapDoor;

    @Override
    public void init() {

        motorRight = hardwareMap.dcMotor.get("motor_1");
        motorLeft = hardwareMap.dcMotor.get("motor_2");
        motorArm = hardwareMap.dcMotor.get("t_rex");
        trapDoor = hardwareMap.servo.get("trap_door");
        motorRight.setDirection(DcMotor.Direction.REVERSE);


    }

    @Override
    public void loop () {

        float left_drive = gamepad1.left_stick_x;
        float right_drive = -gamepad2.left_stick_y;

        left_drive = Range.clip(left_drive, -1, 1);
        right_drive = Range.clip(right_drive, -1, 1);

        motorLeft.setPower(left_drive);
        motorRight.setPower(right_drive);

        float armPosition = -gamepad1.right_stick_y;
        float arm = Range.clip(armPosition, -1, 1);
        motorArm.setPower(arm);

        if (gamepad1.y){
            trapDoor.setPosition(TRAP_DOOR_EXTEND);
        } else {
            trapDoor.setPosition(TRAP_DOOR_CLOSE);
        }
    }

}