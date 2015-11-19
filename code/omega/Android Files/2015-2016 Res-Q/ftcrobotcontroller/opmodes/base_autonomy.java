package com.qualcomm.ftcrobotcontroller.opmodes;


import com.qualcomm.robotcore.eventloop.opmode.LinearOpMode;
import com.qualcomm.robotcore.hardware.DcMotor;
import com.qualcomm.robotcore.hardware.DcMotorController;
import com.qualcomm.robotcore.hardware.GyroSensor;

/**
 * Created by phi on 10/8/2015.
 */
public class base_autonomy extends LinearOpMode {

    DcMotor leftFront;
    DcMotor leftRear;
    DcMotor rightFront;
    DcMotor rightRear;
    DcMotorController dc_1;
    DcMotorController dc_2;
    GyroSensor gyro;

    int rotDirection;
    int state=0;

    @Override
    public void runOpMode() throws InterruptedException {
        gyro = hardwareMap.gyroSensor.get("gyro");
        rightFront = hardwareMap.dcMotor.get("rightFront");
        rightRear = hardwareMap.dcMotor.get("rightRear");
        leftFront = hardwareMap.dcMotor.get("leftFront");
        leftRear = hardwareMap.dcMotor.get("leftRear");
        dc_1 = hardwareMap.dcMotorController.get("dc_1");
        dc_2 = hardwareMap.dcMotorController.get("dc_2");


        leftFront.setDirection(DcMotor.Direction.REVERSE);
        leftRear.setDirection(DcMotor.Direction.REVERSE);


        // wait for the start button to be pressed.
        waitForStart();

        double reqTurnDegrees;

//tc:  I'm thinking for autonomy we can add an array of turn and distance commands so that when it goes active we can
//   just set up a counter as it loops through to execute the sequence of commanded turns and moves in sequence.
// through the array.


        //time.startTime();
        while (opModeIsActive()) {
            switch (state) {
                case 0:
                    reqTurnDegrees = 90.;
                    Turn(reqTurnDegrees);
                    state = state + 1;
                    telemetry.addData("state", state);
                   wait1Msec(200);
                case 1:
                    reqTurnDegrees = -90.;
                    Turn(reqTurnDegrees);
                    state = state + 1;
                    telemetry.addData("state", state);
                    wait1Msec(200);
                default:
                    telemetry.addData("default","default");
                    wait1Msec(5000);
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
        motorSpeed=0.0;
        leftRear.setPower(motorSpeed);
        leftFront.setPower(motorSpeed);
        rightRear.setPower(motorSpeed);
        rightFront.setPower(motorSpeed);



    }

    void executeTurn(double turnDegrees, double Angle, double t1, double time_old, double GyroOld, double maxVelocity, double motorSpeed, double DegreeGain, double MAX_GYRO_SPEED, double MIN_GYRO_SPEED) throws InterruptedException {
        double delta_time;
        double time100 = 0.;
        double GyroNew;
        double degreesToGo;
        //int ii;
        //int ns = 20;
       // double gyroBias;
       // double gyroBias_sum=0.;
        double gyroBias = getBias();
        // tc: may want to average the gyro bias over a few frames instead of just the first value
        //for (ii=1; ii==ns; ii++) {
            //gyroBias = getBias();
        //    gyroBias_sum=gyroBias + gyroBias_sum;
       // }
        //gyroBias=gyroBias_sum/ns;

        telemetry.addData("gyroBias",gyroBias);
        if (turnDegrees < 0) rotDirection = -1;
        else rotDirection = 1;

        //Runs motors at very low power to stop backlash
        motorSpeed = .05;
        leftRear.setPower(rotDirection * motorSpeed);
        leftFront.setPower(rotDirection * motorSpeed);
        rightRear.setPower(-rotDirection * motorSpeed);
        rightFront.setPower(-rotDirection * motorSpeed);
        wait1Msec(10);


        // read the gyro sensor minus the bias offset. GyroBias must be declared and
        // computed in the calling program.

        while ((Math.abs(turnDegrees) - Math.abs(Angle)) > 1) {

            GyroNew = -(gyro.getRotation() - gyroBias);

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
            telemetry.addData("time100", time100);

            wait1Msec(20); // wait 20 ms to allow a reasonable period for the integration

            if (time100 > 10.0) break; // if the bot is not done turning in 5 sec, quit

        }  // end while loop

    }


    //Waits 1t milliseconds
    void wait1Msec(long time) throws InterruptedException {
        sleep(time);
    }
}
