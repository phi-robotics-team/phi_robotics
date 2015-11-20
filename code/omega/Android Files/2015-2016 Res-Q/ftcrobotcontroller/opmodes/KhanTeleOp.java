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
import com.qualcomm.robotcore.util.Range;

/**
 * TeleOp Mode
 * <p>
 * Enables control of the robot via the gamepad
 */
public class KhanTeleOp extends OpMode {

	DcMotor leftFront;
	DcMotor leftRear;
	DcMotor rightFront;
	DcMotor rightRear;
	DcMotor intake;
	/**
	 * Constructor
	 */
	public KhanTeleOp() {

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
		rightFront = hardwareMap.dcMotor.get("rightFront");
		rightRear = hardwareMap.dcMotor.get("rightRear");
		leftFront = hardwareMap.dcMotor.get("leftFront");
		leftRear = hardwareMap.dcMotor.get("leftRear");
		intake = hardwareMap.dcMotor.get("intake");

		rightFront.setDirection(DcMotor.Direction.REVERSE);
		rightRear.setDirection(DcMotor.Direction.REVERSE);
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

		double scl_power = 3.0;

		//Check if the joystick is being used on any axis
		if (Math.abs(gamepad1.left_stick_x) > deadband)
			rawX = gamepad1.left_stick_x - (sgn(gamepad1.left_stick_x) * (float)deadband); //Set variables and subtract deadband from total to avoid jump
		if (Math.abs(gamepad1.left_stick_y) > deadband)
			rawY = gamepad1.left_stick_y - (sgn(gamepad1.left_stick_y) * (float)deadband); //Set variables and subtract deadband from total to avoid jump
		if (Math.abs(gamepad1.right_trigger) > deadband) {

		} //outtake
		//intake
		//Shape the powers based on equation: y = (2/225)(x*abs(x))+(14/45)x
		//Shortened constants from 16 decimal places to 12
		shapedX = (float)0.008888888889 * (rawX * Math.abs(rawX)) + (float)0.311111111111 * rawX;
		shapedY = (float)0.008888888889 * (rawY * Math.abs(rawY)) + (float)0.311111111111 * rawY;
		//shapedX = (float)(2/225) * (rawX * abs(rawX)) + (float)(14/45) * rawX;
		//shapedY = (float)(2/225) * (rawY * abs(rawY)) + (float)(14/45) * rawY;


		shapedX=shapedX*scl_power;
		shapedY=shapedY*scl_power;

		if (shapedX > 1.0) shapedX=1.0;
		if (shapedX < -1.0) shapedX=-1.0;
		if (shapedY > 1.0) shapedY = 1.0;
		if (shapedY < -1.0) shapedY = -1.0;

		//Determine power of each side by slowing one side and increasing the other appropriately
		leftPower = shapedY - shapedX;
		rightPower = shapedY + shapedX;


		if (leftPower > 1.0) leftPower=1.0;
		if (leftPower < -1.0) leftPower=-1.0;
		if (rightPower > 1.0) rightPower = 1.0;
		if (rightPower < -1.0) rightPower= -1.0;


		telemetry.addData("leftPower",leftPower);
		telemetry.addData("rightPower",rightPower);
		//Finally, set the power to the motors
		leftFront.setPower(leftPower);
		leftRear.setPower(leftPower);
		rightFront.setPower(rightPower);
		rightRear.setPower(rightPower);
	}

	private float sgn(float num)
	{
		if (num > 0)
			return 1;
		return -1;
	}
}