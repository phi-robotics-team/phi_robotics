package com.qualcomm.ftcrobotcontroller.opmodes;

import com.qualcomm.robotcore.eventloop.opmode.OpMode;
import com.qualcomm.robotcore.hardware.Servo;

/**
 * Created by phiro on 12/21/2015.
 */
public class SmallFry extends OpMode {

    Servo servo1;


    double EXTEND_POSITION = 0.7;
    double CLOSE_POSITION = 0.0;


    @Override
    public void init() {
        servo1 = hardwareMap.servo.get("left_hand");

    }

    @Override
    public void loop() {

        if(gamepad1.x) {
            servo1.setPosition(EXTEND_POSITION);
        }


        if (gamepad1.y) {
            servo1.setPosition(CLOSE_POSITION);
        }

    }

}
