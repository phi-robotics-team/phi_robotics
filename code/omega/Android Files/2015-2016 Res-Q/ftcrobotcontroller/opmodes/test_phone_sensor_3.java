package com.qualcomm.ftcrobotcontroller.opmodes;

import android.content.Context;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;

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
public class test_phone_sensor_3 extends OpMode implements SensorEventListener {
    private String startDate;
    private SensorManager mSensorManager;
    private Sensor accelerometer;
    private Sensor gyroscope;
    private Sensor magnetometer;
    private Sensor orientation;

    // orientation values
    private float azimuth = 0.0f;      // value in radians
    private float pitch = 0.0f;        // value in radians
    private float roll = 0.0f;         // value in radians

    private float[] mGravity;       // latest sensor values
    private float[] mgyro;   // latest sensor values

    /*
    * Constructor
    */
    public test_phone_sensor_3() {

    }

    /*
    * Code to run when the op mode is first enabled goes here
    * @see com.qualcomm.robotcore.eventloop.opmode.OpMode#init()
    */
    @Override
    public void init() {
        mSensorManager = (SensorManager) hardwareMap.appContext.getSystemService(Context.SENSOR_SERVICE);
        accelerometer = mSensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);
        magnetometer = mSensorManager.getDefaultSensor(Sensor.TYPE_MAGNETIC_FIELD);
        gyroscope = mSensorManager.getDefaultSensor(Sensor.TYPE_GYROSCOPE);


        azimuth = 0.0f;      // value in radians
        pitch = 0.0f;        // value in radians
        roll = 0.0f;

        telemetry.addData("list", mSensorManager.getSensorList(Sensor.TYPE_ALL));
    }

    /*
* Code to run when the op mode is first enabled goes here
* @see com.qualcomm.robotcore.eventloop.opmode.OpMode#start()
*/
    @Override
    public void start() {
        startDate = new SimpleDateFormat("yyyy/MM/dd HH:mm:ss").format(new Date());

        // delay value is SENSOR_DELAY_UI which is ok for telemetry, maybe not for actual robot use
        mSensorManager.registerListener(this, accelerometer, SensorManager.SENSOR_DELAY_UI);
        mSensorManager.registerListener(this, magnetometer, SensorManager.SENSOR_DELAY_UI);
       // mSensorManager.registerListener(this, orientation, SensorManager.SENSOR_ORIENTATION);
        mSensorManager.registerListener(this, gyroscope, SensorManager.SENSOR_DELAY_UI);
    }

    /*
    * This method will be called repeatedly in a loop
    * @see com.qualcomm.robotcore.eventloop.opmode.OpMode#loop()
    */
    @Override
    public void loop() {
//        telemetry.addData("1 Start", "OrientOp started at " + startDate);
//        telemetry.addData("2 note1", "values below are in degrees" );
//        telemetry.addData("3 note2", "azimuth relates to magnetic north" );
//        telemetry.addData("4 note3", " " );
        telemetry.addData("azimuth", Math.round(Math.toDegrees(azimuth)));
        telemetry.addData("pitch", Math.round(Math.toDegrees(pitch)));
        telemetry.addData("roll", Math.round(Math.toDegrees(roll)));

    }

    /*
    * Code to run when the op mode is first disabled goes here
    * @see com.qualcomm.robotcore.eventloop.opmode.OpMode#stop()
    */
    @Override
    public void stop() {
        mSensorManager.unregisterListener(this);
    }

    public void onAccuracyChanged(Sensor sensor, int accuracy) {
        // not sure if needed, placeholder just in case
    }

    public void onSensorChanged(SensorEvent event) {
        // we need both sensor values to calculate orientation
        // only one value will have changed when this method called, we assume we can still use the other value.
        telemetry.addData("sensor type",event.sensor.getType());
        telemetry.addData("sensor accel", Sensor.TYPE_ACCELEROMETER);
        telemetry.addData("sensor magnetometer", Sensor.TYPE_MAGNETIC_FIELD);

        telemetry.addData("sensor gyro", Sensor.TYPE_GYROSCOPE);

        if (event.sensor.getType() == Sensor.TYPE_ACCELEROMETER) {
            mGravity = event.values;
        }
        if (event.sensor.getType() == Sensor.TYPE_GYROSCOPE) {
            mgyro = event.values;
            azimuth = mgyro[0]; // orientation contains: azimuth, pitch and roll
            pitch = mgyro[1];
            roll = mgyro[2];
            telemetry.addData("gyro_x", azimuth);
            telemetry.addData("gyro_y", pitch);
            telemetry.addData("gyro_z", roll);
        }

    }
}