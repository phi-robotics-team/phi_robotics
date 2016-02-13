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

public class blue_auto_color_sensor_in_5_test extends LinearOpMode {

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
    GyroSensor gyro;
    DcMotorController.DeviceMode devMode_a;
    DcMotorController.DeviceMode devMode_b;
    ColorSensor sensorRGB;

    int rotDirection;
    int state = 0;
    //Flag_Gyro is a flag to determine which gyro is being used. 1=ModernRobotics gyro; 2=HiTechnicx
    int Flag_Gyro = 1;


    // wheel and motor info to calculate the # of counts on encoder per inch of distance 'cnts_distin'
    double diam = 4.0;
    //long cnts_motorrev = 1440;
    long cnts_motorrev = 1120;
    double dist_wheelrev = 3.1416 * diam;
    double motorrev_wheelrev = 1.0;  //gear ratio
    double cnts_distin = cnts_motorrev * motorrev_wheelrev / dist_wheelrev;


    double lcolorinit = 0.5;
    double rcolorinit = 0.5;
    double gyroheading;

    double flapclose;
    double flapopen;
    double flapservoPosition;


    @Override
    public void runOpMode() throws InterruptedException {
        gyro = hardwareMap.gyroSensor.get("gyro");
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

        flapclose = 0.40;
        flapopen = 1.0;
        flapservoPosition = flapclose;
        flapservo.setPosition(flapservoPosition);
        telemetry.addData("flapservo pos", flapservo.getPosition());


        rightFront.setDirection(DcMotor.Direction.REVERSE);
        rightRear.setDirection(DcMotor.Direction.REVERSE);

        rcolorservo.setPosition(rcolorinit);
        lcolorservo.setPosition(lcolorinit);
        wait1Msec(20);
        // wait for the start button to be pressed.
        waitForStart();

        // calibrate the gyro.
        if (Flag_Gyro == 1) gyro.calibrate();
        wait1Msec(3500);
        telemetry.addData("donecalibrating", "donecalibrating");

        sensorRGB.enableLed(false);

        double reqTurnDegrees;
        double power;
        double dist;

        rhookservo.setPosition(1.0);
        lhookservo.setPosition(0.0);
        tmservo.setPosition(0.2);
        wait1Msec(20);
        rcolorservo.setPosition(rcolorinit);
        lcolorservo.setPosition(lcolorinit);
        wait1Msec(20);

        // make sure the gyro is calibrated.
        if (Flag_Gyro == 1) {
            while (gyro.isCalibrating()) {
                Thread.sleep(50);
            }
        }

        leftFront.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);
        rightFront.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);
        rightRear.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);
        leftRear.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);
        leftFront.setChannelMode(DcMotorController.RunMode.RUN_WITHOUT_ENCODERS);
        rightFront.setChannelMode(DcMotorController.RunMode.RUN_WITHOUT_ENCODERS);
        leftRear.setChannelMode(DcMotorController.RunMode.RUN_WITHOUT_ENCODERS);
        rightRear.setChannelMode(DcMotorController.RunMode.RUN_WITHOUT_ENCODERS);
        telemetry.addData("dc_runmode", dc_1.getMotorControllerDeviceMode());


        while (opModeIsActive()) {
            switch (state) {
                case 0:
                    dist = 11.0;
                    power = 1.0;
                    MoveEncoder(dist, power);
                    telemetry.addData("state", state);
                    state = state + 1;
                    wait1Msec(200);
                    break;
                case 1:
                    reqTurnDegrees = 20;
                    Turn(reqTurnDegrees);
                    telemetry.addData("state", state);
                    state = state + 1;
                    wait1Msec(200);
                    break;
                case 2:
                    intake.setPower(-1.0F);
                    dist = 42.6;
                    power = 0.5;
                    MoveEncoder(dist, power);
                    telemetry.addData("state", state);
                    state = state + 1;
                    wait1Msec(200);
                    break;
                case 3:
                    reqTurnDegrees = 35;
                    Turn(reqTurnDegrees);
                    telemetry.addData("state", state);
                    state = state + 1;
                    wait1Msec(200);
                    break;
                case 4:
                    dist = 6.0;
                    power = 0.2;
                    MoveEncoder(dist, power);
                    intake.setPower(0.0F);
                    telemetry.addData("state", state);
                    state = state + 1;
                    wait1Msec(200);
                    break;
                case 5:
                    dist = -0.25;
                    power = 0.2;
                    MoveEncoder(dist, power);
                    intake.setPower(0.0F);
                    telemetry.addData("state", state);
                    state = state + 1;
                    wait1Msec(200);
                    break;

                    /*leftRear.setPower(0.5);
                    leftFront.setPower(0.5);
                    rightRear.setPower(0.5);
                    rightFront.setPower(0.5);
                    wait1Msec(200);
                    leftRear.setPower(0);
                    leftFront.setPower(0);
                    rightRear.setPower(0);
                    rightFront.setPower(0);
                    wait1Msec(200);
                    state = state + 1;
                    break;*/
                case 6:
                    sensorRGB.enableLed(false);
                    wait1Msec(50);
                    telemetry.addData("Red", sensorRGB.red());
                    telemetry.addData("Green", sensorRGB.green());
                    telemetry.addData("Blue", sensorRGB.blue());
                    telemetry.addData("Alpha",sensorRGB.alpha());
                    telemetry.addData("Before if", "Before if");
                    wait1Msec(5000);
                    //if it's red, it will press the blue button
                    if (sensorRGB.red() == 1 && sensorRGB.blue() == 0)
                    {
                        lcolorservo.setPosition(0.3);
                        rcolorservo.setPosition(rcolorinit);
                        wait1Msec(1000);
                        lcolorservo.setPosition(lcolorinit);
                    }
                    //if it's blue, it will press the blue button
                    else if (sensorRGB.blue() == 1 && sensorRGB.red() == 0)
                    {
                        rcolorservo.setPosition(0.7);
                        lcolorservo.setPosition(lcolorinit);
                        wait1Msec(1000);
                        rcolorservo.setPosition(rcolorinit);
                    }
                    //something has obviously gone wrong...keep the button-pushers up
                    else
                    {
                        //set lcolorservo and rcolorservo to upward position
                        rcolorservo.setPosition(rcolorinit);
                        lcolorservo.setPosition(lcolorinit);
                        telemetry.addData("Red", sensorRGB.red());
                        telemetry.addData("Green", sensorRGB.green());
                        telemetry.addData("Blue", sensorRGB.blue());
                    }
                    telemetry.addData("Red", sensorRGB.red());
                    telemetry.addData("Green", sensorRGB.green());
                    telemetry.addData("Blue", sensorRGB.blue());
                    telemetry.addData("Out of if","out of if");
                    wait1Msec(200);
                    break;

                default:
                    telemetry.addData("Red", sensorRGB.red());
                    telemetry.addData("Green", sensorRGB.green());
                    telemetry.addData("Blue", sensorRGB.blue());

                    break;
            }

            waitOneFullHardwareCycle();

        }
    }


    //Gets the bias for the gyro
    double getBias() {
        return gyro.getRotation();
    }


    // Executes the gyro turn
    void Turn(double turnDegrees) throws InterruptedException {
        double Angle = 0.0;
        double t1 = this.time;
        double time_old = 0.0;
        double GyroOld = 0.0;
        double maxVelocity = 180.0;
        double motorSpeed = 0.5;
        double DegreeGain = 1.0;
        double MAX_GYRO_SPEED = .85; //maximum motor speed allowed in turns
        double MIN_GYRO_SPEED = .40; //minimum motor speed allowed in turns


        executeTurn(turnDegrees, Angle, t1, time_old, GyroOld, maxVelocity, motorSpeed, DegreeGain, MAX_GYRO_SPEED, MIN_GYRO_SPEED);

        // since we have now reached the target rotation (the while loop is done), stop all drive motors
        //  tc:  may want to move after while-loop in 'execute turn', but it should not matter...
        motorSpeed = 0.0;
        leftRear.setPower(motorSpeed);
        leftFront.setPower(motorSpeed);
        rightRear.setPower(motorSpeed);
        rightFront.setPower(motorSpeed);


    }

    void executeTurn(double turnDegrees, double Angle, double t1, double time_old, double GyroOld, double maxVelocity, double motorSpeed, double DegreeGain, double MAX_GYRO_SPEED, double MIN_GYRO_SPEED) throws InterruptedException {
        double delta_time = 0.;
        double time100 = 0.;
        double GyroNew;
        double degreesToGo;
        double gyroBias = 0.;
        long rotDirection;
        int headingBias = 0;



        if (Flag_Gyro == 1)
        {
            headingBias = gyro.getHeading();

            if (headingBias > 180) headingBias = headingBias - 360;
        }

        else {gyroBias = getBias();}




        if (turnDegrees < 0) rotDirection = -1;
        else rotDirection = 1;

        //Runs motors at very low power to stop backlash
        motorSpeed = .05;
        leftRear.setPower(rotDirection * motorSpeed);
        leftFront.setPower(rotDirection * motorSpeed);
        rightRear.setPower(-rotDirection * motorSpeed);
        rightFront.setPower(-rotDirection * motorSpeed);
        wait1Msec(10);


        //set first time_old to be current time.  Since delta_time tends to be 10-12 millisecs.  The wait1Msec(10) is appropriate
        time_old = t1;

        while ((Math.abs(turnDegrees) - Math.abs(Angle)) > 3) {

            if (Flag_Gyro == 1)
            {
                int heading = 0;
                heading = gyro.getHeading();

                if (heading > 180) heading = heading-360;

                Angle = heading-headingBias;
                // this timer wraps around
                t1 = this.time;
                time = t1;
                delta_time = Math.abs(time - time_old); // delta time in s
                time_old=time;
            }

            else
            {
                // read the gyro sensor minus the bias offset. GyroBias must be declared and
                // computed in the calling program.
                GyroNew = -(gyro.getRotation() - gyroBias);
                //GyroNew = -(gyro.rawZ() - gyroBias);
                // this timer wraps around
                t1 = this.time;
                time = t1;
                delta_time = Math.abs(time - time_old); // delta time in s
                //tc: since the 'delta_time' is in secs changed the '1' to '.001'
                if (delta_time < .001) // protect against divide by zero
                {
                    delta_time = .001;
                }
                // limit the gyro to the max achievable by the bot to minimize data spikes.
                if (Math.abs(GyroNew) > maxVelocity) GyroNew = Math.signum(GyroNew) * maxVelocity;

                // deadband for the gyro to eliminate drift due to noise
                if (Math.abs(GyroNew) <= 0.2) GyroNew = 0.0;

                // compute the integral of the angular rate using a trapazoidal approximation
                // http://en.wikipedia.org/wiki/Numerical_integration

                //tc: since the 'delta_time' is in secs already took out the .001*
                Angle = Angle + delta_time * 0.5 * (GyroNew + GyroOld);

                // update the old values for the next time through the loop
                time_old = time;
                GyroOld = GyroNew;
            }

            // Calculate the rotation remaining
            degreesToGo = Math.abs(turnDegrees) - Math.abs(Angle);

            // motor speed is proportional to the amount of rotation remaining
            motorSpeed = (DegreeGain * Math.abs(degreesToGo));

            // limit the motor speed to be greater than .40 and less than .85
            if (Math.abs(motorSpeed) > MAX_GYRO_SPEED) motorSpeed = MAX_GYRO_SPEED;
            if (Math.abs(motorSpeed) < MIN_GYRO_SPEED) motorSpeed = MIN_GYRO_SPEED;


            leftRear.setPower(rotDirection * motorSpeed);
            leftFront.setPower(rotDirection * motorSpeed);
            rightRear.setPower(-rotDirection * motorSpeed);
            rightFront.setPower(-rotDirection * motorSpeed); // side moves forward for (+) CW rotation\





            //tc: modified so that the 'time100' is incremented every frame
            time100 = delta_time + time100;




            wait1Msec(20); // wait 20 ms to allow a reasonable period for the integration

            if (time100 > 10.0) break; // if the bot is not done turning in 5 sec, quit

        }  // end while loop

    }

    void MoveEncoder(double dist, double power) throws InterruptedException {
        double leftFrontCurrentEncoder = 0;
        double rightFrontCurrentEncoder = 0;
        double leftRearCurrentEncoder = 0;
        double rightRearCurrentEncoder = 0;
        double compensate;
        double t1;
        gyroheading = gyro.getHeading();
        //  long tdly=50;
        long tdly = 20;

        leftFront.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);
        rightFront.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);
        wait1Msec(tdly);
        leftRear.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);
        rightRear.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);
        wait1Msec(tdly);
        leftFront.setChannelMode(DcMotorController.RunMode.RUN_USING_ENCODERS);
        rightFront.setChannelMode(DcMotorController.RunMode.RUN_USING_ENCODERS);
        wait1Msec(tdly);
        leftRear.setChannelMode(DcMotorController.RunMode.RUN_USING_ENCODERS);
        rightRear.setChannelMode(DcMotorController.RunMode.RUN_USING_ENCODERS);

        wait1Msec(tdly);

        //Runs motors at very low power to stop backlash
        double motorSpeed = .05;
        leftRear.setPower(motorSpeed);
        leftFront.setPower(motorSpeed);
        rightRear.setPower(motorSpeed);
        rightFront.setPower(motorSpeed);
        wait1Msec(20);
        motorSpeed=0.0;
        leftRear.setPower(motorSpeed);
        leftFront.setPower(motorSpeed);
        rightRear.setPower(motorSpeed);
        rightFront.setPower(motorSpeed);
        wait1Msec(20);

        double cnt_target = cnts_distin * dist;
        if (dist < 0) power = -power;


        telemetry.addData("power", power);

        leftFront.setPower(power);
        rightFront.setPower(power);
        leftRear.setPower(power);
        rightRear.setPower(power);
        wait1Msec(tdly);

        //dc_1.setMotorControllerDeviceMode(DcMotorController.DeviceMode.READ_ONLY);
        // dc_2.setMotorControllerDeviceMode(DcMotorController.DeviceMode.READ_ONLY);
        //wait1Msec(tdly);



        //while (rightFrontCurrentEncoder < Math.abs(cnt_target) && leftFrontCurrentEncoder < Math.abs(cnt_target)) {
        while((Math.abs(rightFrontCurrentEncoder + leftFrontCurrentEncoder) / 2) < Math.abs(cnt_target) && (Math.abs(rightRearCurrentEncoder + leftRearCurrentEncoder) / 2) < Math.abs(cnt_target)) {

            compensate = gyrocompensate(gyro, gyroheading);
            if (compensate != 1) {
                leftFront.setPower(power * (-compensate));
                rightFront.setPower(power * compensate);
                leftRear.setPower(power * (-compensate));
                rightRear.setPower(power * compensate);

            } else {
                leftFront.setPower(power);
                rightFront.setPower(power);
                leftRear.setPower(power);
                rightRear.setPower(power);
            }
            t1 = this.time;
            // If we've switched to read mode, we can read data from the NXT device.
            // Only necessary on NXT devices.

            // Update the reads after some loops, when the command has successfully propagated through.
           /* telemetry.addData("leftFront Power", leftFront.getPower());
            telemetry.addData("rightFront power", rightFront.getPower());
            telemetry.addData("leftRear Power", leftRear.getPower());
            telemetry.addData("rightRear power", rightRear.getPower());*/

            rightFrontCurrentEncoder = rightFront.getCurrentPosition();
            leftFrontCurrentEncoder = leftFront.getCurrentPosition();
            rightRearCurrentEncoder = rightRear.getCurrentPosition();
            leftRearCurrentEncoder = leftRear.getCurrentPosition();

            if (dist < 0) {
                telemetry.addData("rightFrontCurrentEncoder", rightFrontCurrentEncoder);
                telemetry.addData("leftFrontCurrentEncoder", leftFrontCurrentEncoder);
                telemetry.addData("rightRearCurrentEncoder", rightRearCurrentEncoder);
                telemetry.addData("leftRearCurrentEncoder", leftRearCurrentEncoder);
            }


            wait1Msec(tdly);
            /*DbgLog.msg(String.format("Data2-Time- %.03f", t1));
            DbgLog.msg(String.format("Data2-RightFrontEncoder- %.03f", (float) rightFrontCurrentEncoder));
            DbgLog.msg(String.format("Data2-leftFront.getPower- %.03f", (float) leftFront.getPower()));
            DbgLog.msg(String.format("getTargetPosn_LF - %.03f", (float) leftFront.getTargetPosition()));
            DbgLog.msg(String.format("Data2-LeftFrontEncoder- %.03f", (float) leftFrontCurrentEncoder));*/

            //wait1Msec(2000);
            // Only needed on Nxt devices, but not on USB devices


        }

        rightFrontCurrentEncoder = rightFront.getCurrentPosition();
        leftFrontCurrentEncoder = leftFront.getCurrentPosition();
        rightRearCurrentEncoder = rightRear.getCurrentPosition();
        leftRearCurrentEncoder = leftRear.getCurrentPosition();

        if (dist < 0) {
            telemetry.addData("rightFrontCurrentEncoder", rightFrontCurrentEncoder);
            telemetry.addData("leftFrontCurrentEncoder", leftFrontCurrentEncoder);
            telemetry.addData("rightRearCurrentEncoder", rightRearCurrentEncoder);
            telemetry.addData("leftRearCurrentEncoder", leftRearCurrentEncoder);
        }


        //dc_1.setMotorControllerDeviceMode(DcMotorController.DeviceMode.WRITE_ONLY);
        //dc_2.setMotorControllerDeviceMode(DcMotorController.DeviceMode.WRITE_ONLY);
        wait1Msec(tdly);
        // telemetry.addData("inside loop", "yes");
        leftFront.setPower(0.0);
        rightFront.setPower(0.0);
        rightRear.setPower(0.0);
        leftRear.setPower(0.0);
        wait1Msec(tdly);
        leftFront.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);
        rightFront.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);
        wait1Msec(tdly);
        leftRear.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);
        rightRear.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);
        wait1Msec(tdly);
        leftFront.setChannelMode(DcMotorController.RunMode.RUN_WITHOUT_ENCODERS);
        rightFront.setChannelMode(DcMotorController.RunMode.RUN_WITHOUT_ENCODERS);
        wait1Msec(tdly);
        leftRear.setChannelMode(DcMotorController.RunMode.RUN_WITHOUT_ENCODERS);
        rightRear.setChannelMode(DcMotorController.RunMode.RUN_WITHOUT_ENCODERS);
    }

    private boolean withinMarginOfError(int goal, int value) {
        int lowerMargin = goal - 5;
        int upperMargin = goal + 5;
        return (value >= lowerMargin && value <= upperMargin);
    }

    //Waits 1t milliseconds
    void wait1Msec(long time) throws InterruptedException {
        Thread.sleep(time);
        return;
    }
    private double gyrocompensate(GyroSensor gyro, double initialheading)
    {
        int heading;
        double compensate = 0;
        double gain = 0.02;
        double compvar = 0.2;

        if (initialheading > 180) initialheading = initialheading-360;

        heading = gyro.getHeading();
        if (heading > 180) heading = heading-360;

        if (heading > initialheading + 5)
        {
            compensate = heading * gain;
            if (compensate > compvar) compensate = compvar;
        }
        else if (heading < initialheading - 5)
        {
            //tc:  if heading is negative (nose left), then compensate is positive, and you will turn more nose left...
            //tc:   suggest taking negative out of '-gain'...
            compensate = heading * gain;
            if (compensate < -compvar) compensate = -compvar;
        }
        else
        {
            compensate = 1;
        }


        return compensate;
    }

}
