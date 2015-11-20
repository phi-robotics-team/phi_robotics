package com.qualcomm.ftcrobotcontroller.opmodes;

import com.qualcomm.robotcore.eventloop.opmode.LinearOpMode;
import com.qualcomm.robotcore.hardware.DcMotor;
import com.qualcomm.robotcore.hardware.DcMotorController;


/**
 * Created by thcox on 10/26/2015.
 */
public class test_move_old_nxt extends LinearOpMode {

    DcMotor frontLeft;
    DcMotor frontRight;
    DcMotor rearLeft;
    DcMotor rearRight;

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

        frontLeft = hardwareMap.dcMotor.get("leftFront");
        frontRight = hardwareMap.dcMotor.get("rightFront");
        rearLeft = hardwareMap.dcMotor.get("leftRear");
        rearRight = hardwareMap.dcMotor.get("rightRear");

        frontLeft.setDirection(DcMotor.Direction.REVERSE);
        rearLeft.setDirection(DcMotor.Direction.REVERSE);

        dc_1= hardwareMap.dcMotorController.get("dc_1");
        dc_2= hardwareMap.dcMotorController.get("dc_2");

        frontLeft.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);
        frontRight.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);
        rearLeft.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);
        rearRight.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);


        waitForStart();

        frontLeft.setChannelMode(DcMotorController.RunMode.RUN_TO_POSITION);
        frontRight.setChannelMode(DcMotorController.RunMode.RUN_TO_POSITION);
        rearLeft.setChannelMode(DcMotorController.RunMode.RUN_TO_POSITION);
        rearRight.setChannelMode(DcMotorController.RunMode.RUN_TO_POSITION);


      /* frontLeft.setChannelMode(DcMotorController.RunMode.RUN_USING_ENCODERS);
        frontRight.setChannelMode(DcMotorController.RunMode.RUN_USING_ENCODERS);
        rearLeft.setChannelMode(DcMotorController.RunMode.RUN_USING_ENCODERS);
        rearRight.setChannelMode(DcMotorController.RunMode.RUN_USING_ENCODERS); */


        while (opModeIsActive()) {


            double dist_in = 24.0;
            double cnt_target= cnts_distin * dist_in;
            telemetry.addData("dist_in",dist_in);
            telemetry.addData("cnts_distin",cnts_distin);
            telemetry.addData("cnts_target",cnt_target);

          /*  if ( numOpLoops % 5 == 0) {
                // Note: If you are using the NxtDcMotorController, you need to switch into "read" mode
                // before doing a read, and into "write" mode before doing a write. This is because
                // the NxtDcMotorController is on the I2C interface, and can only do one at a time. If you are
                // using the USBDcMotorController, there is no need to switch, because USB can handle reads
                // and writes without changing modes. The NxtDcMotorControllers start up in "write" mode.
                // This method does nothing on USB devices, but is needed on Nxt devices.
                telemetry.addData("in numoploops",numOpLoops);
                dc_1.setMotorControllerDeviceMode(DcMotorController.DeviceMode.READ_ONLY);
                dc_2.setMotorControllerDeviceMode(DcMotorController.DeviceMode.READ_ONLY);
                telemetry.addData("in numoploops 2", numOpLoops);
                flc= -frontLeft.getCurrentPosition();
                frc= -frontRight.getCurrentPosition();
                rlc= rearLeft.getCurrentPosition();
                rrc = rearRight.getCurrentPosition();
                telemetry.addData("in numopLoops 3",numOpLoops);



            }

            telemetry.addData("flc",flc);
            telemetry.addData("frc",frc);
            telemetry.addData("rlc",rlc);
            telemetry.addData("rrc",rrc);
            telemetry.addData("cnt_target",(int) cnt_target);


*/
           // if (flc < cnt_target && frc < cnt_target && rlc < cnt_target && rrc < cnt_target) {
                telemetry.addData("in if cnt_target", flc);
                frontLeft.setTargetPosition((int) -cnt_target);
                frontRight.setTargetPosition((int) cnt_target);
                rearLeft.setTargetPosition((int) -cnt_target);
                rearRight.setTargetPosition((int) cnt_target);
                telemetry.addData("in if cnt_target 2", flc);

                frontLeft.setPower(0.7);
                frontRight.setPower(0.7);
                rearLeft.setPower(0.7);
                rearRight.setPower(0.7);
                numOpLoops = 1;
                telemetry.addData("in if cnt_target 3", flc);

            //}
            //else {
               // frontLeft.setPower(0.0);
               // frontRight.setPower(0.0);
               // rearLeft.setPower(0.0);
               // rearRight.setPower(0.0);
            //}
            numOpLoops = numOpLoops + 1;

            waitOneFullHardwareCycle();
        }


    }

}