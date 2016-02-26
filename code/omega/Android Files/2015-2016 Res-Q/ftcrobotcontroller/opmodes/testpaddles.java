package com.qualcomm.ftcrobotcontroller.opmodes;

import com.qualcomm.ftccommon.DbgLog;
import com.qualcomm.robotcore.eventloop.opmode.LinearOpMode;
import com.qualcomm.robotcore.hardware.ColorSensor;
import com.qualcomm.robotcore.hardware.DcMotor;
import com.qualcomm.robotcore.hardware.DcMotorController;
import com.qualcomm.robotcore.hardware.GyroSensor;
import com.qualcomm.robotcore.hardware.Servo;
import com.qualcomm.robotcore.util.Range;

/**
 * Created by phi on 1/11/2016.
 */

public class testpaddles extends LinearOpMode {

    DcMotor leftFront;
    DcMotor leftRear;
    DcMotor rightFront;
    DcMotor rightRear;
    DcMotor intake;
    DcMotor lift;
    Servo lhookservo;
    Servo rhookservo;
    Servo tmservo;
    Servo flapservo;
    Servo lcolorservo;
    Servo rcolorservo;
    DcMotorController dc_1;
    DcMotorController dc_2;
    //GyroSensor gyro;
    DcMotorController.DeviceMode devMode_a;
    DcMotorController.DeviceMode devMode_b;
    ColorSensor sensorRGB;

    int rotDirection;
    int state = 0;
    //Flag_Gyro is a flag to determine which gyro is being used. 1=ModernRobotics gyro; 2=HiTechnicx
    //int Flag_Gyro = 1;


    // wheel and motor info to calculate the # of counts on encoder per inch of distance 'cnts_distin'
    double diam = 4.0;
    long cnts_motorrev = 1440;
    //long cnts_motorrev = 1120;
    double dist_wheelrev = 3.1416 * diam;
    double motorrev_wheelrev = 1.0;
    double cnts_distin = cnts_motorrev * motorrev_wheelrev / dist_wheelrev;

   // double lcolorinit = 1.0;
   // double rcolorinit = 0.0;
     double lcolorinit = 1.0;
     double rcolorinit = 0.0;
    double rcservoPosition;
    double rcservoDelta=.0001;


    @Override
    public void runOpMode() throws InterruptedException {
        //gyro = hardwareMap.gyroSensor.get("gyro");
        rightFront = hardwareMap.dcMotor.get("R-Front_Motor");
        rightRear = hardwareMap.dcMotor.get("R-Rear_Motor");
        leftFront = hardwareMap.dcMotor.get("L-Front_Motor");
        leftRear = hardwareMap.dcMotor.get("L-Rear_Motor");
        intake = hardwareMap.dcMotor.get("intake");
        lift = hardwareMap.dcMotor.get("lift");
        lhookservo = hardwareMap.servo.get("L-Hook_Servo");
        rhookservo = hardwareMap.servo.get("R-Hook_Servo");
        tmservo = hardwareMap.servo.get("tmservo");
        flapservo = hardwareMap.servo.get("Flap_Servo");
        lcolorservo = hardwareMap.servo.get("leftColor");
        rcolorservo = hardwareMap.servo.get("rightColor");
        dc_1 = hardwareMap.dcMotorController.get("dc_1");
        dc_2 = hardwareMap.dcMotorController.get("dc_2");
        sensorRGB = hardwareMap.colorSensor.get("sensorRGB");

        dc_1.setMotorControllerDeviceMode(DcMotorController.DeviceMode.READ_WRITE);
        dc_2.setMotorControllerDeviceMode(DcMotorController.DeviceMode.READ_WRITE);

        // calibrate the gyro.
        //if (Flag_Gyro == 1) gyro.calibrate();

        sensorRGB.enableLed(false);

        rcolorservo.setPosition(rcolorinit);
        lcolorservo.setPosition(lcolorinit);

        leftFront.setDirection(DcMotor.Direction.REVERSE);
        leftRear.setDirection(DcMotor.Direction.REVERSE);


        // wait for the start button to be pressed.
        waitForStart();

        double reqTurnDegrees;
        double power;
        double dist;

        rhookservo.setPosition(1.0);
        lhookservo.setPosition(0.0);
        tmservo.setPosition(0.0);
        rcolorservo.setPosition(rcolorinit);
        lcolorservo.setPosition(lcolorinit);

        // make sure the gyro is calibrated.
        /**if (Flag_Gyro == 1) {
            while (gyro.isCalibrating()) {
                Thread.sleep(50);
            }
        }*/

        leftFront.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);
        rightFront.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);
        telemetry.addData("dc_runmode", dc_1.getMotorControllerDeviceMode());


        while (opModeIsActive()) {
            switch (state) {
                /*case 0:
                    rcolorservo.setPosition(0.7);
                    lcolorservo.setPosition(0.3);
                    wait1Msec(1000);
                    rcolorservo.setPosition(rcolorinit);
                    lcolorservo.setPosition(lcolorinit);
                    telemetry.addData("state", state);
                    state = state + 1;
                    wait1Msec(200);
                    break;*/

                case 0:
                   // rcolorservo.setPosition(0.7);
                  //  wait1Msec(5000);
                    rcolorservo.setPosition(rcolorinit);
                    wait1Msec(1000);
                    while (rcservoPosition < .45) {
                        rcservoPosition += rcservoDelta;
                        telemetry.addData("rcservoPosition", rcservoPosition);
                        rcservoPosition = Range.clip(rcservoPosition, 0, 1);
                        rcolorservo.setPosition(rcservoPosition);
                    }
                    //wait1Msec(1000);
                    //lcolorservo.setPosition(lcolorinit);
                    state = state + 1;
                    wait1Msec(200);
                    break;

                /**case 1:
                    reqTurnDegrees = -40;
                    Turn(reqTurnDegrees);
                    telemetry.addData("state", state);
                    state = state + 1;
                    wait1Msec(200);
                    break;
                case 2:
                    //intake.setPower(-1.0F);
                    dist = 16.0;
                    power = 1.0;
                    MoveEncoder(dist, power);
                    telemetry.addData("state", state);
                    state = state + 1;
                    wait1Msec(200);
                    break;
                case 3:
                    reqTurnDegrees = -20;
                    Turn(reqTurnDegrees);
                    telemetry.addData("state", state);
                    state = state + 1;
                    wait1Msec(200);
                    break;
                case 4:
                    dist = 5.0;
                    power = 0.5;
                    MoveEncoder(dist, power);
                    intake.setPower(0.0F);
                    telemetry.addData("state", state);
                    state = state + 1;
                    wait1Msec(200);
                    break;
                case 5:
                    //if it's red, it will press the blue button
                    if (sensorRGB.red() == 1)
                    {
                        lcolorservo.setPosition(lbutton);
                    }
                    //if it's blue, it will press the blue button
                    else if (sensorRGB.blue() == 1)
                    {
                        rcolorservo.setPosition(rbutton);
                    }
                    //something has obviously gone wrong...keep the button-pushers up
                    else
                    {
                        //set lcolorservo and rcolorservo to upward position
                    }*/

                default:

                    break;
            }

            waitOneFullHardwareCycle();

        }
    }
    //Waits 1t milliseconds
    void wait1Msec(long time) throws InterruptedException {
        Thread.sleep(time);
        return;
    }

}
