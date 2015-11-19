package com.qualcomm.ftcrobotcontroller.opmodes;

import com.qualcomm.ftccommon.DbgLog;
import com.qualcomm.robotcore.eventloop.opmode.OpMode;
import com.qualcomm.robotcore.hardware.DcMotor;
import com.qualcomm.robotcore.hardware.DcMotorController;

/**
 * Created by thcox on 10/22/2015.
 */
public class test_encoderTest_2 extends OpMode {


    DcMotorController.DeviceMode devMode_a;
    DcMotorController.DeviceMode devMode_b;
    // DcMotorController wheelController;
    // DcMotor motorRight;
    // DcMotor motorLeft;
    DcMotor leftFront;
    DcMotor leftRear;
    DcMotor rightFront;
    DcMotor rightRear;
    DcMotorController dc_1;
    DcMotorController dc_2;

    int rightFrontCurrentEncoder;
    int leftFrontCurrentEncoder;
    int rightRearCurrentEncoder;
    int leftRearCurrentEncoder;
    int leftFrontTargetEncoder;
    int rightFrontTargetEncoder;
    int leftRearTargetEncoder;
    int rightRearTargetEncoder;

    DcMotorController.RunMode motorRightRunMode;
    DcMotorController.RunMode motorLeftRunMode;

    int numOpLoops = 1;

    double diam = 4.0;
    long cnts_motorrev = 1120;
    double dist_wheelrev = 3.14 * diam;
    double motorrev_wheelrev = .33;
    double cnts_distin = cnts_motorrev * motorrev_wheelrev / dist_wheelrev;


    double distin = 24.0;
    int firstTarget = 0;

    State state;

    public enum State {
        STATE_ZERO,
        STATE_ONE,
        STATE_TWO
    }


    /**
     * Constructor
     */
    public test_encoderTest_2() {

    }

    @Override
    public void init() {


    }

    /*
     * Code to run when the op mode is first enabled goes here
     * @see com.qualcomm.robotcore.eventloop.opmode.OpMode#start()
     */
    @Override
    public void start() {

        state = State.STATE_ZERO;

        leftFront = hardwareMap.dcMotor.get("leftFront");
        leftRear = hardwareMap.dcMotor.get("leftRear");
        rightRear = hardwareMap.dcMotor.get("rightRear");
        rightFront = hardwareMap.dcMotor.get("rightFront");

        dc_1 = hardwareMap.dcMotorController.get("dc_1");
        dc_2 = hardwareMap.dcMotorController.get("dc_2");
        devMode_a = DcMotorController.DeviceMode.WRITE_ONLY;
        devMode_b = DcMotorController.DeviceMode.WRITE_ONLY;

        leftFront.setDirection(DcMotor.Direction.REVERSE);
        leftRear.setDirection(DcMotor.Direction.REVERSE);

        // set the mode
        // Nxt devices start up in "write" mode by default, so no need to switch device modes here.
        leftFront.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);
        // leftRear.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);
        rightFront.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);
        // rightRear.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);


        motorLeftRunMode = DcMotorController.RunMode.RUN_USING_ENCODERS;
        motorRightRunMode = DcMotorController.RunMode.RUN_USING_ENCODERS;

    }

    /*
     * This method will be called repeatedly in a loop
     * @see com.qualcomm.robotcore.eventloop.opmode.OpMode#loop()
     */
    @Override
    public void loop() {
        DbgLog.error("mode_a: " + devMode_a);
        DbgLog.error("mode_b: " + devMode_b);

        // The op mode should only use "write" methods (setPower, setChannelMode, etc) while in
        // WRITE_ONLY mode.

        if (devMode_a == DcMotorController.DeviceMode.WRITE_ONLY && devMode_b == DcMotorController.DeviceMode.WRITE_ONLY) {
            switch (state) {
                case STATE_ZERO:
                    leftFront.setChannelMode(DcMotorController.RunMode.RUN_TO_POSITION);
                    rightFront.setChannelMode(DcMotorController.RunMode.RUN_TO_POSITION);
                    telemetry.addData("distin", distin);
                    telemetry.addData("cnts_distin", cnts_distin);


                    int firstTarget = (int) (distin * cnts_distin);

                    telemetry.addData("firstTarget", firstTarget);

                    leftFront.setTargetPosition(firstTarget);
                    rightFront.setTargetPosition(firstTarget);

                    // telemetry.addData("left device mode", devMode_a);
                    // telemetry.addData("right device mode", devMode_b);

                    leftFront.setPower(1.0);
                    rightFront.setPower(1.0);
                    leftRear.setPower(1.0);
                    rightRear.setPower(1.0);

                    if (withinMarginOfError(firstTarget, rightFrontCurrentEncoder) &&
                            withinMarginOfError(firstTarget, leftFrontCurrentEncoder)) {
                        state = State.STATE_ONE;
                    }
                    break;
                case STATE_ONE:
                    //  if (withinMarginOfError(firstTarget, rightFrontCurrentEncoder) &&
                    //       withinMarginOfError(firstTarget, leftFrontCurrentEncoder)) {
                {
                    telemetry.addData("inside loop", "yes");
                    leftFront.setPower(0.0);
                    rightFront.setPower(0.0);
                    rightRear.setPower(0.0);
                    leftRear.setPower(0.0);
                }
                break;
            }


            // To read any values from the NXT controllers, we need to switch into READ_ONLY mode.
            // It takes time for the hardware to switch, so you can't switch modes within one loop of the
            // op mode. Every 17th loop, this op mode switches to READ_ONLY mode.
            if (numOpLoops % 5 == 0) {
                // Note: If you are using the NxtDcMotorController, you need to switch into "read" mode
                // before doing a read, and into "write" mode before doing a write. This is because
                // the NxtDcMotorController is on the I2C interface, and can only do one at a time. If you are
                // using the USBDcMotorController, there is no need to switch, because USB can handle reads
                // and writes without changing modes. The NxtDcMotorControllers start up in "write" mode.
                // This method does nothing on USB devices, but is needed on Nxt devices.
                dc_1.setMotorControllerDeviceMode(DcMotorController.DeviceMode.READ_ONLY);
                dc_2.setMotorControllerDeviceMode(DcMotorController.DeviceMode.READ_ONLY);
                if (withinMarginOfError(firstTarget, rightFrontCurrentEncoder) &&
                        withinMarginOfError(firstTarget, leftFrontCurrentEncoder)) {

                    telemetry.addData("inside loop", "yes");
                    leftFront.setPower(0.0);
                    rightFront.setPower(0.0);
                    rightRear.setPower(0.0);
                    leftRear.setPower(0.0);
                }
            }

            // If we've switched to read mode, we can read data from the NXT device.
            // Only necessary on NXT devices.
            if (devMode_a == DcMotorController.DeviceMode.READ_ONLY && devMode_b == DcMotorController.DeviceMode.READ_ONLY) {

                // Update the reads after some loops, when the command has successfully propagated through.
                telemetry.addData("leftFront Power", leftFront.getPower());
                telemetry.addData("rightFront power", rightFront.getPower());
                telemetry.addData("leftRear Power", leftRear.getPower());
                telemetry.addData("rightRear power", rightRear.getPower());

                telemetry.addData("left device mode", devMode_a);
                telemetry.addData("right device mode", devMode_b);

                rightFrontCurrentEncoder = rightFront.getCurrentPosition();
                leftFrontCurrentEncoder = leftFront.getCurrentPosition();
                // rightRearCurrentEncoder = rightRear.getCurrentPosition();
                // leftRearCurrentEncoder = leftRear.getCurrentPosition();

                telemetry.addData("right front curr enc", rightFrontCurrentEncoder);
                telemetry.addData("left front curr enc", leftFrontCurrentEncoder);
                // telemetry.addData("right rear curr enc", rightRearCurrentEncoder);
                // telemetry.addData("left rear curr enc", leftRearCurrentEncoder);

                leftFrontTargetEncoder = leftFront.getTargetPosition();
                rightFrontTargetEncoder = rightFront.getTargetPosition();
                // leftRearTargetEncoder = leftRear.getTargetPosition();
                // rightRearTargetEncoder = rightRear.getTargetPosition();

                telemetry.addData("right front target", rightFrontTargetEncoder);
                telemetry.addData("left front target", leftFrontTargetEncoder);
                // telemetry.addData("right rear target", rightRearTargetEncoder);
                // telemetry.addData("left rear target", leftRearTargetEncoder);

                // Only needed on Nxt devices, but not on USB devices
                dc_1.setMotorControllerDeviceMode(DcMotorController.DeviceMode.WRITE_ONLY);
                dc_2.setMotorControllerDeviceMode(DcMotorController.DeviceMode.WRITE_ONLY);

                // Reset the loop
                numOpLoops = 0;
            }

            // Update the current devMode
            devMode_a = dc_1.getMotorControllerDeviceMode();
            devMode_b = dc_2.getMotorControllerDeviceMode();
            numOpLoops++;

        }
    }

    /*
     * Code to run when the op mode is first disabled goes here
     * @see com.qualcomm.robotcore.eventloop.opmode.OpMode#stop()
     */
    @Override
    public void stop() {


    }

    private boolean withinMarginOfError(int goal, int value) {
        int lowerMargin = goal - 5;
        int upperMargin = goal + 5;
        return (value >= lowerMargin && value <= upperMargin);
    }

}