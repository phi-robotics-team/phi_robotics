package com.qualcomm.ftcrobotcontroller.opmodes;

import com.qualcomm.robotcore.eventloop.opmode.OpMode;
import com.qualcomm.robotcore.hardware.Servo;

/**
 * Created by phiro on 12/16/2015.
 */
public class ServoProgram extends OpMode {

    Servo servo1;

    final double SERVO_EXTEND = 1.0;
    final double SERVO_CLOSE = 0.0;

    @Override
    public void init() {
        servo1 = hardwareMap.servo.get("TestServo");
    }

    @Override
    public void loop() {

       if (gamepad1.y)  {
           servo1.setPosition(SERVO_EXTEND);
       } else {
           servo1.setPosition(SERVO_CLOSE);
       }

    }

}
