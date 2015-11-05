package com.qualcomm.ftcrobotcontroller.opmodes;

import android.os.SystemClock;
import com.qualcomm.robotcore.eventloop.opmode.LinearOpMode;
import com.qualcomm.robotcore.hardware.DcMotor;
import com.qualcomm.robotcore.hardware.DcMotorController;
import com.qualcomm.robotcore.hardware.GyroSensor;

import java.util.Date;
import java.util.concurrent.TimeUnit;

/**
 * Created by thcox on 10/27/2015.
 */
public class test_turn_gyro extends LinearOpMode {
    DcMotor leftFront;
    DcMotor leftRear;
    DcMotor rightFront;
    DcMotor rightRear;
    GyroSensor gyro;
    Double reqTurnDegrees;
    Float biasSetter;
    double gyroBias;

    double gyroActual;
    double bias;

    @Override
    public void runOpMode() throws InterruptedException {

       // gyro = hardwareMap.gyroSensor.get("gyro");
        //touch=hardwareMap.touchSensor.get("touch");

        // wait for the start button to be pressed.
        waitForStart();
        reqTurnDegrees = 90.0;
        gyroBias = getBias();

        //time.startTime();
        while (opModeIsActive()) {

            Turn(reqTurnDegrees);
            waitOneFullHardwareCycle();
            //time.reset();
        }
    }





    /**
     * ***************************************************************************************
     */

    //Gets the bias for the gyro
    double getBias() {
        return gyro.getRotation();
    }

    //Zeros the gyro

    /**
     * double zeroGyro()
     * {
     * gyroBias = gyro.getRotation();
     * return gyroBias;
     * }
     */

    // Executes the gyro turn
    void Turn(double turnDegrees) {
        double Angle = 0.0;
        double t1 = SystemClock.uptimeMillis() / 1000.0;
        double time_old = 0.0;
        double GyroOld = 0.0;
        double maxVelocity = 180.0;
        double motorSpeed = 0.0;
        double DegreeGain = 5.0;
        long MAX_GYRO_SPEED = 85; //maximum motor speed allowed in turns
        long MIN_GYRO_SPEED = 40; //minimum motor speed allowed in turns


        gyro = hardwareMap.gyroSensor.get("gyro");
        rightFront = hardwareMap.dcMotor.get("rightFront");
        rightRear = hardwareMap.dcMotor.get("rightRear");
        leftFront = hardwareMap.dcMotor.get("leftFront");
        leftRear = hardwareMap.dcMotor.get("leftRear");

        leftFront.setDirection(DcMotor.Direction.REVERSE);
        leftRear.setDirection(DcMotor.Direction.REVERSE);

        // remove the backlash and freeplay from the motors before zeroing the encoders by commanding
        // a very low power for a short time

        /**motorSpeed = 5;
         leftRear.setPower(-rotDirection * motorSpeed);
         leftFront.setPower(-rotDirection * motorSpeed);
         rightRear.setPower(rotDirection * motorSpeed);
         rightFront.setPower(rotDirection * motorSpeed);
         wait1Msec(10);*/

        // reset the back motor encoders to zero
        //DcMotorController.DeviceMode.READ_WRITE();
        /**leftFront.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);
         rightFront.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);
         leftRear.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);
         rightRear.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);*/

        executeTurn(turnDegrees, Angle, t1, time_old, GyroOld, maxVelocity, motorSpeed, DegreeGain, MAX_GYRO_SPEED, MIN_GYRO_SPEED);

    }

    void executeTurn(double turnDegrees, double Angle, double t1, double time_old, double GyroOld, double maxVelocity, double motorSpeed, double DegreeGain, long MAX_GYRO_SPEED, long MIN_GYRO_SPEED) {
        double delta_time;
        double GyroNew;
        double degreesToGo;
        int rotDirection;
        if (turnDegrees < 0) rotDirection = -1;
        else rotDirection = 1;

        // read the gyro sensor minus the bias offset. GyroBias must be declared and
        // computed in the calling program.
        GyroNew = -(gyro.getRotation() - gyroBias);
        while ((Math.abs(turnDegrees) - Math.abs(Angle)) > 3) {
            time = t1; // this timer wraps around
            delta_time = Math.abs(time - time_old); // delta time in ms

            if (delta_time < 1) // protect against divide by zero
            {
                delta_time = 1;
            }


            // limit the gyro to the max achievable by the bot to minimize data spikes.
            if (Math.abs(GyroNew) > maxVelocity) GyroNew = Math.signum(GyroNew) * maxVelocity;

            // deadband for the gyro to eliminate drift due to noise
            if (Math.abs(GyroNew) <= 0.2) GyroNew = 0.0;

            // compute the integral of the angular rate using a trapazoidal approximation
            // http://en.wikipedia.org/wiki/Numerical_integration
            Angle = Angle + 0.001 * (float) delta_time * 0.5 * (GyroNew + GyroOld);

            // update the old values for the next time through the loop
            time_old = time;
            GyroOld = GyroNew;

            // Calculate the rotation remaining
            degreesToGo = Math.abs(turnDegrees) - Math.abs(Angle);

            // motor speed is proportional to the amount of rotation remaining
            motorSpeed = (int) (DegreeGain * Math.abs(degreesToGo));

            // limit the motor speed to be greater than 15 and less than 75
            if (Math.abs(motorSpeed) > MAX_GYRO_SPEED) motorSpeed = MAX_GYRO_SPEED;
            if (Math.abs(motorSpeed) < MIN_GYRO_SPEED) motorSpeed = MIN_GYRO_SPEED;

            //leftRear.setPower(-rotDirection * motorSpeed);
            //leftFront.setPower(-rotDirection * motorSpeed);
            //rightRear.setPower(rotDirection * motorSpeed);
            //rightFront.setPower(rotDirection * motorSpeed); // side moves forward for (+) CCW rotation
            telemetry.addData("GyroOld", GyroOld);
            telemetry.addData("Angle", Angle);
            double time100 = delta_time;
            time100 = delta_time + time100;

            if (time100 > 5.0) break; // if the bot is not done turning in 5 sec, quit
            wait1Msec(15F); // wait 20 ms to allow a reasonable period for the integration

            wait1Msec(100);

            //Runs motors at very low power to stop backlash


            /**motorSpeed = 5;
             leftRear.setPower(-rotDirection * motorSpeed);
             leftFront.setPower(-rotDirection * motorSpeed);
             rightRear.setPower(rotDirection * motorSpeed);
             rightFront.setPower(rotDirection * motorSpeed);
             wait1Msec(10);*/

            // reset the back motor encoders to zero
            //DcMotorController.DeviceMode.READ_WRITE();
            /**leftFront.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);
             rightFront.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);
             leftRear.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);
             rightRear.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);*/

        }  // End while rotation remaining

        // since we have now reached the target rotation (the while loop is done), stop all drive motors

        //leftRear.setPower(0);
        //leftFront.setPower(0);
        //rightRear.setPower(0);
        //rightFront.setPower(0);

        // reset the back motor encoders to zero
        /**leftFront.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);
         rightFront.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);
         leftRear.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);
         rightRear.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);*/
    }

    //Waits 1t milliseconds
    float wait1Msec(float time) {
        return time;
    }

}
