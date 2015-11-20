
package com.qualcomm.ftcrobotcontroller.opmodes;

import android.os.SystemClock;

import com.qualcomm.robotcore.eventloop.opmode.LinearOpMode;
import com.qualcomm.robotcore.hardware.DcMotor;
import com.qualcomm.robotcore.hardware.GyroSensor;

/**
 * Created by phi on 10/8/2015.
 */
public class TurnGyro_mod_t extends LinearOpMode {

    DcMotor leftFront;
    DcMotor leftRear;
    DcMotor rightFront;
    DcMotor rightRear;
    GyroSensor gyro;
    Double reqTurnDegrees;
    Float biasSetter;

    double gyroActual;
    double bias;
    int ii=0;
    int jj=0;



    @Override
    public void runOpMode() throws InterruptedException {
        gyro = hardwareMap.gyroSensor.get("gyro");
        //temp






        //touch=hardwareMap.touchSensor.get("touch");

        // wait for the start button to be pressed.
        waitForStart();
        double gyroBias;
        double Angle = 0.0;
        double angle_o = 0.0;
        gyroBias = getBias();
        double time_old = 0.0;
        double ttp = 0.0;
        double GyroOld = 0.0;
        double delta_time;
        //tc: moved init of 'time100' to here and set to zero.  E
        double time100 = 0.;
        double GyroNew;
        reqTurnDegrees = 90.0;
        int ii=1;
        int ns=20;
        double gyroBias_sum = 0;


        /*for (ii=1; ii==ns; ii++) {
            gyroBias = getBias();
            gyroBias_sum=gyroBias + gyroBias_sum;
        }


        gyroBias=gyroBias_sum/ns;*/

        //time.startTime();
        while (opModeIsActive()) {
           //telemetry.addData("gyroBias_sum",gyroBias_sum);
                double t1 = SystemClock.uptimeMillis() / 1000.0;
                double tt=this.time;
                bias = getBias();
                time = t1;
                delta_time = time - time_old;
                double dtt= tt - ttp;
                double del_time = dtt;
            if (ii==1) angle_o= Angle;
                telemetry.addData("time", time);
                telemetry.addData("time_old", time_old);
                telemetry.addData("delta_time", delta_time);
                GyroNew = -(gyro.getRotation() - gyroBias);
                telemetry.addData("gyroOld", GyroOld);
                telemetry.addData("gyroNew", GyroNew);
                telemetry.addData("gyroBias", gyroBias);
                //temp ck integration
                //tc: since the 'delta_time' is in secs already took out the .001*
                Angle = Angle +  del_time * 0.5 * (GyroNew + GyroOld); //- angle_o;
                time_old = time;
                ttp = tt;
                GyroOld = GyroNew;
                telemetry.addData("Angle", Angle);
            telemetry.addData("angle_o",angle_o);

            wait1Msec(20);

            //Turn(reqTurnDegrees);

            //tc:  added one TM statement to make sure it gets back to the turn
            //tc:  also for the sake of testing I'll print it
            //telemetry.addData("after turn: reqTurnDegrees", reqTurnDegrees);
            waitOneFullHardwareCycle();
            ii = 2;
        }
    }

    //tc: removed a bunch of non-used code...

    /*******************************************************************************************/

    //Gets the bias for the gyro
    double getBias()
    {
        return gyro.getRotation();
    }


    // Executes the gyro turn
    void Turn (double turnDegrees) throws InterruptedException {
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

        //tc: moved some of the motor manipulation to remove non-linear backlash  and
        //    reset encoders to be prior to executeturn call

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

        //temp
       /* telemetry.addData("t1_pre_exec", t1);
        ii=ii+1;
        telemetry.addData("pre_exec", ii);
        executeTurn(turnDegrees, Angle, t1, time_old, GyroOld, maxVelocity, motorSpeed, DegreeGain, MAX_GYRO_SPEED, MIN_GYRO_SPEED);
*/

        //tc: moved some of the motor manipulation done after while is complete to be here, just to cleanup

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

    void executeTurn (double turnDegrees, double Angle, double t1, double time_old, double GyroOld, double maxVelocity, double motorSpeed, double DegreeGain, long MAX_GYRO_SPEED, long MIN_GYRO_SPEED) throws InterruptedException {
        double delta_time;
        //tc: moved init of 'time100' to here and set to zero.  E
        double time100 = 0.;
        double GyroNew;
        double gyroBias = 0;
        double degreesToGo;
        int rotDirection;
        jj=jj+1;
        telemetry.addData("in_exec,",jj);
        if (turnDegrees < 0) rotDirection = -1;
        else rotDirection = 1;

        // read the gyro sensor minus the bias offset. GyroBias must be declared and
        // computed in the calling program.

      //  while ((Math.abs(turnDegrees) - Math.abs(Angle)) > 3) {
            //tc: moved 'GyroNew' calc to be within while loop so that it is updated as the robot turns
            GyroNew = -(gyro.getRotation() - gyroBias);
            telemetry.addData("t1_inexec", t1);
            time = t1; // this timer wraps around
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
            Angle = Angle + (float) delta_time * 0.5 * (GyroNew + GyroOld);

            telemetry.addData("delta_time", delta_time);
            telemetry.addData("time", time);
            telemetry.addData("time_old", time_old);
            // update the old values for the next time through the loop
            time_old = time;
            telemetry.addData("time_old_2", time_old);
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
            //tc: added a bunch of TM statements
            telemetry.addData("GyroOld", GyroOld);
            telemetry.addData("GyroNew", GyroNew);
            telemetry.addData("gyroBias", gyroBias);
            telemetry.addData("delta_time", delta_time);
            telemetry.addData("t1", t1);
            telemetry.addData("Angle", Angle);



            //tc: modified so that the 'time100' is incremented every frame
            time100 = delta_time + time100;
            telemetry.addData("time100", time100);
            double t2 = SystemClock.uptimeMillis() / 1000.0;
            wait1Msec(20); // wait 20 ms to allow a reasonable period for the integration
            double t3 = SystemClock.uptimeMillis() / 1000.0;
            double tw=t3-t2;
            telemetry.addData("dt_20",tw);
           // if (time100 > 5.0) break; // if the bot is not done turning in 5 sec, quit

            //wait1Msec(100);

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

       // }   // End while rotation remaining
        telemetry.addData("Angle_afterWhile",Angle);


    }

    //Waits 1t milliseconds
    void wait1Msec (long time) throws InterruptedException {
        //tc: added sleep function so it waits
        sleep(time);
        return;
    }
}
