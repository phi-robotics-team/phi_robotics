/* Copyright (c) 2014 Qualcomm Technologies Inc
All rights reserved.
Redistribution and use in source and binary forms, with or without modification,
are permitted (subject to the limitations in the disclaimer below) provided that
the following conditions are met:
Redistributions of source code must retain the above copyright notice, this list
of conditions and the following disclaimer.
Redistributions in binary form must reproduce the above copyright notice, this
list of conditions and the following disclaimer in the documentation and/or
other materials provided with the distribution.
Neither the name of Qualcomm Technologies Inc nor the names of its contributors
may be used to endorse or promote products derived from this software without
specific prior written permission.
NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY THIS
LICENSE. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */

        package com.qualcomm.ftcrobotcontroller.opmodes;

        import com.qualcomm.robotcore.eventloop.opmode.OpMode;
        import com.qualcomm.robotcore.hardware.DcMotor;
        import com.qualcomm.robotcore.hardware.Servo;
        import com.qualcomm.robotcore.util.Range;

/**
 * TeleOp Mode
 * <p>
 * Enables control of the robot via the gamepad
 */
public class Unicorn2 extends OpMode {

    final static double tmservo_MIN_RANGE  = 0.0;
    final static double tmservo_MAX_RANGE  = 1.0;

    final static double flapservo_MIN_RANGE  = 0.20;
    final static double flapservo_MAX_RANGE  = 1.0;

    final static double hookservo_MIN_RANGE  = 0.20;
    final static double hookservo_MAX_RANGE  = 1.0;

    // position of the tmservo servo
    double tmservoPosition;

    // position of the flapservo servo
    double flapservoPosition;

    // position of the hookservo servos
    double hookservoPosition;

    // amount to change the tmservo servo position by
    double tmservoDelta = 0.0025;

    int tanktoggle = 0;

    //previous X button initialized
    boolean prev_x = false;

    DcMotor leftFront;
    DcMotor leftRear;
    DcMotor rightFront;
    DcMotor rightRear;
    DcMotor intake;
    Servo tmservo;
    Servo flapservo;
    Servo lhookservo;
    Servo rhookservo;
    DcMotor lift;
    /**
     * Constructor
     */
    public Unicorn2() {

    }

    /*
     * Code to run when the op mode is initialized goes here
     *
     * @see com.qualcomm.robotcore.eventloop.opmode.OpMode#init()
     */
    @Override
    public void init() {


		/*
		 * Use the hardwareMap to get the dc motors and servos by name. Note
		 * that the names of the devices must match the names used when you
		 * configured your robot and created the configuration file.
		 */
		
		/*
		 * For the demo Tetrix K9 bot we assume the following,
		 *   There are two motors "motor_1" and "motor_2"
		 *   "motor_1" is on the right side of the bot.
		 *   "motor_2" is on the left side of the bot and reversed.
		 *   
		 * We also assume that there are two servos "servo_1" and "servo_6"
		 *    "servo_1" controls the arm joint of the manipulator.
		 *    "servo_6" controls the tmservo joint of the manipulator.
		 */
        rightFront = hardwareMap.dcMotor.get("rightFront");
        rightRear = hardwareMap.dcMotor.get("rightRear");
        leftFront = hardwareMap.dcMotor.get("leftFront");
        leftRear = hardwareMap.dcMotor.get("leftRear");
        intake = hardwareMap.dcMotor.get("intake");
        lift = hardwareMap.dcMotor.get("lift");

        rightFront.setDirection(DcMotor.Direction.REVERSE);
        rightRear.setDirection(DcMotor.Direction.REVERSE);

        //Tape Measure
        tmservo = hardwareMap.servo.get("servo_6");
        tmservoPosition = 0.2;
        tmservo.setPosition(tmservoPosition);
        telemetry.addData("pos", tmservo.getPosition());

        flapservo = hardwareMap.servo.get("servo_1");
        //flapservoPosition = 0.5;
        flapservoPosition = 0.3;
        flapservo.setPosition(flapservoPosition);
        telemetry.addData("pos", flapservo.getPosition());

        lhookservo = hardwareMap.servo.get("servo_2");
        rhookservo = hardwareMap.servo.get("servo_3");
        rhookservo.setPosition(0.0);
        lhookservo.setPosition(1.0);

        telemetry.addData("rhook posn", rhookservo.getPosition());
        telemetry.addData("lhook posn", lhookservo.getPosition());


    }

    /*
     * This method will be called repeatedly in a loop
     *
     * @see com.qualcomm.robotcore.eventloop.opmode.OpMode#run()
     */
    @Override
    public void loop() {

        Drive();
    }

    //when we press the button, we want the motors to move to turn the conveyor
    //R1 will be intake, R2 is outtake
    //R1 will be counterclockwise, R2 will be clockwise
    //one motor
    //We need to name the motor and define counterclockwise and clockwise
	/*
	 * Code to run when the op mode is first disabled goes here
	 * 
	 * @see com.qualcomm.robotcore.eventloop.opmode.OpMode#stop()
	 */
    @Override
    public void stop() {

    }

    public void Drive()
    {
        //Define storage variables
        int deadband = 0;
        double rawX = 0;
        double rawY = 0;
        double shapedX, shapedY;
        double leftPower, rightPower;
        double lhookservopos = 1.0;
        double rhookservopos = 0.0;


        double scl_power = 3.0;

        //Check if the joystick is being used on any axis
        if (Math.abs(gamepad1.left_stick_x) > deadband)
            rawX = gamepad1.left_stick_x - (sgn(gamepad1.left_stick_x) * (float)deadband); //Set variables and subtract deadband from total to avoid jump
        if (Math.abs(gamepad1.left_stick_y) > deadband)
            rawY = gamepad1.left_stick_y - (sgn(gamepad1.left_stick_y) * (float)deadband); //Set variables and subtract deadband from total to avoid jump
        // Shape the powers based on equation: y = (2/225)(x*abs(x))+(14/45)x
        // Shortened constants from 16 decimal places to 12
       // shapedX = (float)0.008888888889 * (rawX * Math.abs(rawX)) + (float)0.311111111111 * rawX;
        //shapedY = (float)0.008888888889 * (rawY * Math.abs(rawY)) + (float)0.311111111111 * rawY;
		 shapedX = (float)0.25 * (rawX * Math.abs(rawX)) + (float)0.07 * rawX;
         shapedY = (float)0.25 * (rawY * Math.abs(rawY)) + (float)0.07 * rawY;
 
        //shapedX = (float)(2/225) * (rawX * abs(rawX)) + (float)(14/45) * rawX;
        //shapedY = (float)(2/225) * (rawY * abs(rawY)) + (float)(14/45) * rawY;


        shapedX=shapedX*scl_power;
        shapedY=shapedY*scl_power;

        if (shapedX > 1.0) shapedX= 1.0;
        if (shapedX < -1.0) shapedX= -1.0;
        if (shapedY > 1.0) shapedY = 1.0;
        if (shapedY < -1.0) shapedY = -1.0;

        //Determine power of each side by slowing one side and increasing the other appropriately
        leftPower = shapedY + shapedX;
        rightPower = shapedY - shapedX;


        if (leftPower > 1.0) leftPower= 1.0;
        if (leftPower < -1.0) leftPower= -1.0;
        if (rightPower > 1.0) rightPower = 1.0;
        if (rightPower < -1.0) rightPower= -1.0;

        telemetry.addData("leftPower",leftPower);
        telemetry.addData("rightPower",rightPower);
        //Finally, set the power to the motors
        leftFront.setPower(leftPower);
        leftRear.setPower(leftPower);
        rightFront.setPower(rightPower);
        rightRear.setPower(rightPower);
        //intake power
        float intakePower = 1.0F;
        float winchPower = 1.0F;
        //INTAKE
       /* if (gamepad1.back)
        {
            switch (tanktoggle) {
                case 0:
                default: {
                    tanktoggle = 1;
                }
                case 1: {
                    tanktoggle = 0;
                }
            }

        } //intake*/
        //INTAKE
        if (gamepad1.right_bumper)
        {
            intake.setPower(-intakePower);
        } //intake
        else if (gamepad1.right_trigger > 0)
        {
            intake.setPower(intakePower);
        } //output
        else
        {
            intake.setPower(0.0F);
        }
        //WINCH
        if (gamepad1.left_bumper)
        {
            lift.setPower(-winchPower);
        } //intake
        else if (gamepad1.left_trigger > 0)
        {
            lift.setPower(winchPower);
        } //output
        else
        {
            lift.setPower(0.0F);
        }

        // update the position of the tape measure servo
        if (gamepad1.y) {
            tmservoPosition += tmservoDelta;
            telemetry.addData("gamepadY", "Y pressed");
        }

        if (gamepad1.a) {
            tmservoPosition -= tmservoDelta;
            telemetry.addData("gamepadA", "A pressed");
        }
        telemetry.addData("tmservoposition", tmservoPosition);
        // clip the position values so that they never exceed their allowed range.
        tmservoPosition = Range.clip(tmservoPosition, tmservo_MIN_RANGE, tmservo_MAX_RANGE);

        // write position values to the wrist and tmservo servo
        tmservo.setPosition(tmservoPosition);

        if (gamepad1.x && !prev_x)
        {
            if (flapservoPosition > 0.7)
            {
                //flapservo.setPosition(0.5);
                flapservoPosition = 0.30;
            }
            else
            {
                //flapservo.setPosition(1.0);
                flapservoPosition = 1.0;
                telemetry.addData("inside else- x pressed", gamepad1.x);
            }
        //flapservo.setPosition(flapservo.getPosition() + 0.1);
            //telemetry.addData("xpressed", true);
        }
        /**else
        {
            telemetry.addData("xpressed", false);
        }*/

        prev_x = gamepad1.x;

        telemetry.addData("flapservoposition", flapservoPosition);
        // clip the position values so that they never exceed their allowed range.
        flapservoPosition = Range.clip(flapservoPosition, flapservo_MIN_RANGE, flapservo_MAX_RANGE);

        // write position values to the wrist and tmservo servo
        flapservo.setPosition(flapservoPosition);


        telemetry.addData("back button",gamepad1.back);
        telemetry.addData("start button",gamepad1.start);
        if (gamepad1.start)
        {
            lhookservopos=.5;
            rhookservopos=.5;
            telemetry.addData("lhook - back",lhookservopos);

        }

        //telemetry.addData("hookservoposition", hookservoPosition);
        // clip the position values so that they never exceed their allowed range.
        //lhookservopos = Range.clip(lhookservopos, hookservo_MIN_RANGE, hookservo_MAX_RANGE);
        //rhookservopos = Range.clip(rhookservopos, hookservo_MIN_RANGE, hookservo_MAX_RANGE);
        lhookservo.setPosition(lhookservopos);
        rhookservo.setPosition(rhookservopos);
        /*
		 * Send telemetry data back to driver station. Note that if we are using
		 * a legacy NXT-compatible motor controller, then the getPower() method
		 * will return a null value. The legacy NXT-compatible motor controllers
		 * are currently write only.
		 */
        telemetry.addData("Text", "*** Robot Data***");
        telemetry.addData("tmservo", "tmservo:  " + String.format("%.2f", tmservoPosition));
    }


    private float sgn(float num)
    {
        if (num > 0)
            return 1;
        return -1;
    }

}
