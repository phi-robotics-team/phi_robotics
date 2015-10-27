package com.qualcomm.ftcrobotcontroller.opmodes;

import com.qualcomm.robotcore.eventloop.opmode.LinearOpMode;
import com.qualcomm.robotcore.hardware.DcMotor;
import com.qualcomm.robotcore.hardware.DcMotorController;


/**
 * Created by thcox on 10/26/2015.
 */
public class test_move_old_nxt extends LinearOpMode {

    DcMotor front_left;
    DcMotor front_right;
    DcMotor rear_left;
    DcMotor rear_right;

    DcMotorController dc_1;
    DcMotorController dc_2;

    double diam = 4.0;
    long cnts_motorrev = 1120;
    double dist_wheelrev = Math.PI * diam;
    double motorrev_wheelrev= .33;

    int numOpLoops = 1;
    int flc;
    int rrc;
    int frc;
    int rlc;

    double cnts_distin = cnts_motorrev * motorrev_wheelrev / dist_wheelrev;


    @Override
    public void runOpMode() throws InterruptedException {

        front_left = hardwareMap.dcMotor.get("frontLeft");
        front_right = hardwareMap.dcMotor.get("frontRight");
        rear_left = hardwareMap.dcMotor.get("rearLeft");
        rear_right = hardwareMap.dcMotor.get("rearRight");

        front_left.setDirection(DcMotor.Direction.REVERSE);
        rear_left.setDirection(DcMotor.Direction.REVERSE);

        dc_1= hardwareMap.dcMotorController.get("dc_1");
        dc_2= hardwareMap.dcMotorController.get("dc_2");

        front_left.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);
        front_right.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);
        rear_left.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);
        rear_right.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);


        waitForStart();

        /*front_left.setChannelMode(DcMotorController.RunMode.RUN_TO_POSITION);
        front_right.setChannelMode(DcMotorController.RunMode.RUN_TO_POSITION);
        rear_left.setChannelMode(DcMotorController.RunMode.RUN_TO_POSITION);
        rear_right.setChannelMode(DcMotorController.RunMode.RUN_TO_POSITION);
*/

        front_left.setChannelMode(DcMotorController.RunMode.RUN_USING_ENCODERS);
        front_right.setChannelMode(DcMotorController.RunMode.RUN_USING_ENCODERS);
        rear_left.setChannelMode(DcMotorController.RunMode.RUN_USING_ENCODERS);
        rear_right.setChannelMode(DcMotorController.RunMode.RUN_USING_ENCODERS);


        while (opModeIsActive()) {


            double dist_in = 24.0;
            double cnt_target= cnts_distin * dist_in;

            if ( numOpLoops % 5 == 0) {
                // Note: If you are using the NxtDcMotorController, you need to switch into "read" mode
                // before doing a read, and into "write" mode before doing a write. This is because
                // the NxtDcMotorController is on the I2C interface, and can only do one at a time. If you are
                // using the USBDcMotorController, there is no need to switch, because USB can handle reads
                // and writes without changing modes. The NxtDcMotorControllers start up in "write" mode.
                // This method does nothing on USB devices, but is needed on Nxt devices.
                dc_1.setMotorControllerDeviceMode(DcMotorController.DeviceMode.READ_ONLY);
                dc_2.setMotorControllerDeviceMode(DcMotorController.DeviceMode.READ_ONLY);
                flc= -front_left.getCurrentPosition();
                frc= -front_right.getCurrentPosition();
                rlc= rear_left.getCurrentPosition();
                rrc = rear_right.getCurrentPosition();
            }




            if (flc < cnt_target && frc < cnt_target && rlc < cnt_target && rrc < cnt_target) {

                front_left.setTargetPosition((int) -cnt_target);
                front_right.setTargetPosition((int) cnt_target);
                rear_left.setTargetPosition((int) -cnt_target);
                rear_right.setTargetPosition((int) cnt_target);

                front_left.setPower(0.7);
                front_right.setPower(0.7);
                rear_left.setPower(0.7);
                rear_right.setPower(0.7);
                numOpLoops = 1;

            }
            else {
                front_left.setPower(0.0);
                front_right.setPower(0.0);
                rear_left.setPower(0.0);
                rear_right.setPower(0.0);
            }
            numOpLoops = numOpLoops + 1;

            waitOneFullHardwareCycle();
        }


    }

}