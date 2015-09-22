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


    public SaladQueen() {

    }

    @Override
    public void init() {


        motorRight = hardwareMap.dcMotor.get("motor_2");
        motorLeft = hardwareMap.dcMotor.get("motor_1");
        motorLeft.setDirection(DcMotor.Direction.REVERSE);


    }

    @Override
    public void loop() {


        float left_drive = -gamepad1.left_stick_y;
        float right_drive = gamepad1.right_stick_y;

        left_drive = Range.clip(left_drive, -1, 1);
        right_drive = Range.clip(right_drive, -1, 1);

        left_drive = (float)scaleInput(left_drive);
        right_drive =  (float)scaleInput(right_drive);

        motorLeft.setPower(left_drive);
        motorRight.setPower(right_drive);

        }


    /*
     * Code to run when the op mode is first disabled goes here
     *
     * @see com.qualcomm.robotcore.eventloop.opmode.OpMode#stop()
     */
    @Override
    public void stop() {

    }

    double scaleInput(double dVal)  {
        double[] scaleArray = { 0.0, 0.05, 0.09, 0.10, 0.12, 0.15, 0.18, 0.24,
                0.30, 0.36, 0.43, 0.50, 0.60, 0.72, 0.85, 1.00, 1.00 };

        // get the corresponding index for the scaleInput array.
        int index = (int) (dVal * 16.0);
        if (index < 0) {
            index = -index;
        } else if (index > 16) {
            index = 16;
        }

        double dScale = 0.0;
        if (dVal < 0) {
            dScale = -scaleArray[index];
        } else {
            dScale = scaleArray[index];
        }

        return dScale;
    }

}


