package com.qualcomm.ftcrobotcontroller.opmodes;

import android.content.Context;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.SystemClock;

import com.qualcomm.ftccommon.DbgLog;
import com.qualcomm.robotcore.eventloop.opmode.LinearOpMode;
import com.qualcomm.robotcore.hardware.GyroSensor;


import java.util.Date;
//import com.qualcomm.robotcore.util.ElapsedTime;

/**
 * Created by thcox on 10/2/2015.
 */
public class test_phone_sensor extends LinearOpMode {

    private SensorManager mSensorManager;
    private Sensor maccel;
    //time = new ElaspedTime();
    //GyroSensor gyro;

    @Override
    public void runOpMode() throws InterruptedException {
        //double GyroVariable;

        mSensorManager = (SensorManager) hardwareMap.appContext.getSystemService(Context.SENSOR_SERVICE);
        //gyro=hardwareMap.gyroSensor.get("gyro");
        maccel = mSensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);
        //mSensorManager.registerListener( this, maccel, SensorManager.SENSOR_DELAY_UI);

        float accel_x=0;
        float accel_y=0;
        float accel_z=0;

        telemetry.addData(" active accel_x ",accel_x);
        telemetry.addData("active accel_y",accel_y);
        telemetry.addData("active accel_z",accel_z);
        //time.startTime();
        while (opModeIsActive()) {


           // GyroVariable = gyro.getRotation();
           // telemetry.addData("gyro ", GyroVariable);
            telemetry.addData(" active accel_x ",accel_x);
            telemetry.addData("active accel_y",accel_y);
            telemetry.addData("active accel_z",accel_z);
            DbgLog.msg(String.format("Data2 - accel_x = %.03f", accel_x));
            DbgLog.msg(String.format("Data2 - accel_y = %.03f",accel_y));
            DbgLog.msg(String.format("Data2 - accel_z = %.03f",accel_z));
            waitOneFullHardwareCycle();
            //time.reset();
        }
    }

    public void onAccuracyChanged(Sensor sensor, int accuracy) {
        // not sure if needed, placeholder just in case
    }

    public void onSensorChanged(SensorEvent event) {
        // Many sensors return 3 values, one for each axis.
        float accel_x = event.values[0];
        float accel_y = event.values[1];
        float accel_z = event.values[2];

        telemetry.addData("accel_x",accel_x);
        telemetry.addData("accel_y",accel_y);
        telemetry.addData("accel_z",accel_z);
        DbgLog.msg(String.format("Data - accel_x = %.03f", accel_x));
        DbgLog.msg(String.format("Data - accel_y = %.03f",accel_y));
        DbgLog.msg(String.format("Data - accel_z = %.03f",accel_z));

    }
}
