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

/**
 * TeleOp Mode
 * <p>
 * Enables control of the robot via the gamepad
 */
public class test_TeleOp extends OpMode {

	DcMotor leftFront;
	DcMotor leftRear;
	DcMotor rightFront;
	DcMotor rightRear;
	DcMotor conveyM;
	DcMotor lift;


	/**
	 * Constructor
	 */
	public test_TeleOp() {

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
		 *    "servo_6" controls the claw joint of the manipulator.
		 */
		rightFront = hardwareMap.dcMotor.get("front_right");
		rightRear = hardwareMap.dcMotor.get("back_right");
		leftFront = hardwareMap.dcMotor.get("front_left");
		leftRear = hardwareMap.dcMotor.get("back_left");
		lift = hardwareMap.dcMotor.get("lift");

		leftFront.setDirection(DcMotor.Direction.REVERSE);
		leftRear.setDirection(DcMotor.Direction.REVERSE);
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
		float rawX = 0;
		float rawY = 0;
		double conv_p = -.8;
		double conv_p2= -.6;
		float shapedX, shapedY;
		float leftPower, rightPower;
		double convPower;
		double convPower2;
		float scl_power = 3;

		//Check if the joystick is being used on any axis
		if (Math.abs(gamepad1.left_stick_x) > deadband)
			rawX = gamepad1.left_stick_x - (sgn(gamepad1.left_stick_x) * (float)deadband); //Set variables and subtract deadband from total to avoid jump
		if (Math.abs(gamepad1.left_stick_y) > deadband)
			rawY = gamepad1.left_stick_y - (sgn(gamepad1.left_stick_y) * (float)deadband); //Set variables and subtract deadband from total to avoid jump

		//Shape the powers based on equation: y = (2/225)(x*abs(x))+(14/45)x
		//Shortened constants from 16 decimal places to 12
		shapedX = (float)0.008888888889 * (rawX * Math.abs(rawX)) + (float)0.311111111111 * rawX;
		shapedY = (float)0.008888888889 * (rawY * Math.abs(rawY)) + (float)0.311111111111 * rawY;
		//shapedX = (float)(2/225) * (rawX * abs(rawX)) + (float)(14/45) * rawX;
		//shapedY = (float)(2/225) * (rawY * abs(rawY)) + (float)(14/45) * rawY;

		shapedX= shapedX*scl_power;
		shapedY= shapedY*scl_power;


		//Determine power of each side by slowing one side and increasing the other appropriately
		leftPower = shapedY - shapedX;
		rightPower = shapedY + shapedX;

		if (leftPower > 1) leftPower = 1;
		if (rightPower > 1) rightPower = 1;
		if (leftPower < -1) leftPower = -1;
		if (rightPower < -1) rightPower = -1;

//Run conveyor belt
		convPower = 0;
		if (gamepad1.right_bumper)
		{
			convPower = conv_p;
		}

		if (gamepad1.right_trigger > .1)
		{
			convPower = -conv_p;
		}

		convPower2= 0;
		if (gamepad1.left_bumper)
		{
			convPower2 = conv_p2;
		}

		if (gamepad1.left_trigger > .1)
		{
			convPower2 = -conv_p2;
		}


		//Finally, set the power to the motors
		leftFront.setPower(leftPower);
		leftRear.setPower(leftPower);
		rightFront.setPower(rightPower);
		rightRear.setPower(rightPower);
		conveyM.setPower(convPower);
		lift.setPower(convPower2);

		telemetry.addData("leftPower ", leftPower);
		telemetry.addData("rightPower ", rightPower);
		telemetry.addData("shapedX ", shapedX);
		telemetry.addData("shapedY ", shapedY);
		telemetry.addData("convPower ", convPower);
		telemetry.addData("left_stick_x ", gamepad1.left_stick_x);
		telemetry.addData("left_stick_y ", gamepad1.left_stick_y);
		telemetry.addData("rawx ", rawX);
		telemetry.addData("rawy ", rawY);


	}

	private float sgn(float num)
	{
		if (num > 0)
			return 1;
		return -1;
	}
}
