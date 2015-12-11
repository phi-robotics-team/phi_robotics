package com.qualcomm.ftcrobotcontroller.opmodes;

import com.qualcomm.robotcore.eventloop.opmode.OpMode;
import com.qualcomm.robotcore.hardware.Servo;
import com.qualcomm.robotcore.util.Range;

/**
 * Created by phiro on 9/14/2015.
 */
public class ServoMove extends OpMode {



    Servo servo1;
    Servo servo2;


    double EXTEND_POSITION = 0.5;
    double CLOSE_POSITION = 0.0;


    @Override
    public void init() {
        servo1 = hardwareMap.servo.get("left_hand");
        servo2 = hardwareMap.servo.get("right_hand");
    }


    @Override
    public void loop() {



        if(gamepad1.a) {
            servo1.setPosition(EXTEND_POSITION);
        }



        if(gamepad1.b) {
            servo1.setPosition(CLOSE_POSITION);
        }

        if(gamepad1.x) {
            servo2.setPosition(EXTEND_POSITION);
        }



        if(gamepad1.y) {
            servo2.setPosition(CLOSE_POSITION);
        }

    }
}


