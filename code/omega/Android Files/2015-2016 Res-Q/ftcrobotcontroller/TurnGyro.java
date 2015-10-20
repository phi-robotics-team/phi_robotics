package com.qualcomm.ftcrobotcontroller.opmodes;

import android.os.SystemClock;
import com.qualcomm.robotcore.eventloop.opmode.LinearOpMode;
import com.qualcomm.robotcore.hardware.DcMotor;
import com.qualcomm.robotcore.hardware.DcMotorController;

import java.util.concurrent.TimeUnit;

/**
 * Created by phi on 10/8/2015.
 */
public class gyroTurn extends LinearOpMode {

    DcMotor leftFront;
    DcMotor leftRear;
    DcMotor rightFront;
    DcMotor rightRear;

    @Override
    public void runOpMode() throws InterruptedException {
        waitForStart();

        while (opModeIsActive()) {

            void Turn (float turnDegrees)
            {
                // Store new bias
                long state = 2;
                //float GyroBias = 0;
                long time;
                long time_old = 0;
                long delta_time;
                double maxVelocity = 180.0;
                // max angular velocity in deg/sec
                double GyroOld;
                double GyroNew;
                long rotDirection = 1;
                long motorSpeed = 0;
                double DegreeGain = 5.0;
                double degreesToGo;
                long MAX_GYRO_SPEED = 85; //maximum motor speed allowed in turns
                long MIN_GYRO_SPEED = 40; //minimum motor speed allowed in turns
                double Angle;

                rightFront = hardwareMap.dcMotor.get("front_right");
                rightRear = hardwareMap.dcMotor.get("back_right");
                leftFront = hardwareMap.dcMotor.get("front_left");
                leftRear = hardwareMap.dcMotor.get("back_left");

                leftFront.setDirection(DcMotor.Direction.REVERSE);
                leftRear.setDirection(DcMotor.Direction.REVERSE);

                // Determine the rotation direction. Set to negative for clock-wise rotation.
                if (turnDegrees < 0) rotDirection = -1;

                // Set the Angle and components to zero befor turning
                Angle = 0.0;
                degreesToGo = 0.0;
                time_old = nPgmTime;  // Grab the current system time
                GyroOld = 0.0;
                TimeUnit.MILLISECONDS(100);

                // remove the backlash and freeplay from the motors before zeroing the encoders by commanding
                // a very low power for a short time

                motorSpeed = 5;
                leftRear.setPower(-rotDirection * motorSpeed);
                leftFront.setPower(-rotDirection * motorSpeed);
                rightRear.setPower(rotDirection * motorSpeed);
                rightFront.setPower(rotDirection * motorSpeed);
                TimeUnit.MILLISECONDS(10);

                // reset the back motor encoders to zero
                DcMotorController.DeviceMode.READ_WRITE;
                leftFront.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);
                rightFront.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);
                leftRear.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);
                rightRear.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);

                ClearTimer(T3);   //  Reset timer value to zero
                //---------------------------------------------------------------------------
                // Move the motors until the gyro Angle indicates the rotation is complete
                //---------------------------------------------------------------------------
                while ((abs(turnDegrees) - abs(Angle)) > 3) {
                    time = nPgmTime; // this timer wraps around
                    delta_time = abs(time - time_old); // delta time in ms

                    if (delta_time < 1) // protect against divide by zero
                    {
                        delta_time = 1;
                    }
                    // read the gyro sensor minus the bias offset. GyroBias must be declared and
                    // computed in the calling program.
                    GyroNew = -((float) SensorValue[Gyro] - GyroBias);

                    // limit the gyro to the max achievable by the bot to minimize data spikes.
                    if (abs(GyroNew) > maxVelocity) GyroNew = sgn(GyroNew) * maxVelocity;

                    // deadband for the gyro to eliminate drift due to noise
                    if (abs(GyroNew) <= 0.2) GyroNew = 0.0;

                    // compute the integral of the angular rate using a trapazoidal approximation
                    // http://en.wikipedia.org/wiki/Numerical_integration
                    Angle = Angle + 0.001 * (float) delta_time * 0.5 * (GyroNew + GyroOld);

                    // update the old values for the next time through the loop
                    time_old = time;
                    GyroOld = GyroNew;

                    // Calculate the rotation remaining
                    degreesToGo = abs(turnDegrees) - abs(Angle);

                    // motor speed is proportional to the amount of rotation remaining
                    motorSpeed = (int) (DegreeGain * abs(degreesToGo));

                    // limit the motor speed to be greater than 15 and less than 75
                    if (abs(motorSpeed) > MAX_GYRO_SPEED) motorSpeed = MAX_GYRO_SPEED;
                    if (abs(motorSpeed) < MIN_GYRO_SPEED) motorSpeed = MIN_GYRO_SPEED;

                    leftRear.setPower(-rotDirection * motorSpeed);
                    leftFront.setPower(-rotDirection * motorSpeed);
                    rightRear.setPower(rotDirection * motorSpeed);
                    rightFront.setPower(rotDirection * motorSpeed); // side moves forward for (+) CCW rotation

                    if (time100[T3] > 50) break; // if the bot is not done turning in 5 sec, quit
                    wait1Msec(15); // wait 20 ms to allow a reasonable period for the integration

                } // End while rotation remaining

                // since we have now reached the target rotation (the while loop is done), stop all drive motors

                leftRear.setPower(0);
                leftFront.setPower(0);
                rightRear.setPower(0);
                rightFront.setPower(0);

                // reset the back motor encoders to zero
                leftFront.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);
                rightFront.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);
                leftRear.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);
                rightRear.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);

            } // End of Turn_Gyro()
        }
    }
}
