package com.qualcomm.ftcrobotcontroller.opmodes;

import android.content.Context;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;

import com.qualcomm.ftccommon.DbgLog;
import com.qualcomm.robotcore.eventloop.opmode.OpMode;

import java.text.SimpleDateFormat;
import java.util.Date;


/**
 * An op mode that uses the geomagnetic and accelerometer values to calculate device
 * orientation and return those values in telemetry.
 * It makes use of getRotationMatrix() and getOrientation(), but does not use
 * remapCoordinateSystem() which one might want.
 * see: http://developer.android.com/reference/android/hardware/SensorManager.html#remapCoordinateSystem(float[], int, int, float[])
 */
public class test_phone_sensor_1 extends OpMode implements SensorEventListener {

    private SensorManager mSensorManager;
    private Sensor maccel;


    private float accel_x = 0f;
    private float accel_y = 0f;
    private float accel_z = 0f;


    public test_phone_sensor_1() {

    }

    @Override
    public void init() {
        mSensorManager = (SensorManager) hardwareMap.appContext.getSystemService(Context.SENSOR_SERVICE);
        maccel = mSensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);

        accel_x = 0f;
        accel_y = 0f;
        accel_z = 0f;


        telemetry.addData(" active accel_x ", accel_x);
        telemetry.addData("active accel_y", accel_y);
        telemetry.addData("active accel_z", accel_z);

    }


    @Override
    public void start() {
        mSensorManager.registerListener(this, maccel, SensorManager.SENSOR_DELAY_UI);


    }

    @Override
    public void loop() {
        telemetry.addData(" active accel_x ", accel_x);
        telemetry.addData("active accel_y", accel_y);
        telemetry.addData("active accel_z", accel_z);

        DbgLog.msg(String.format("Data2 - accel_x = %.03f", accel_x));
        DbgLog.msg(String.format("Data2 - accel_y = %.03f", accel_y));
        DbgLog.msg(String.format("Data2 - accel_z = %.03f", accel_z));
    }

    @Override
    public void stop() {
        mSensorManager.unregisterListener(this);
    }

    public void onAccuracyChanged(Sensor sensor, int accuracy) {
        // not sure if needed, placeholder just in case
    }

    public void onSensorChanged(SensorEvent event) {
        float accel_x = event.values[0];
        float accel_y = event.values[1];
        float accel_z = event.values[2];


        telemetry.addData("accel_x", accel_x);
        telemetry.addData("accel_y", accel_y);
        telemetry.addData("accel_z", accel_z);

        telemetry.addData("sensor type", event.sensor.getType());
        telemetry.addData("sensor accel", Sensor.TYPE_ACCELEROMETER);
        telemetry.addData("sensor gyro", Sensor.TYPE_GYROSCOPE);
        DbgLog.msg(String.format("Data - accel_x = %.03f", accel_x));
        DbgLog.msg(String.format("Data - accel_y = %.03f", accel_y));
        DbgLog.msg(String.format("Data - accel_z = %.03f", accel_z));

    }
}
