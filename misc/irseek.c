#pragma platform(FTC)         // Only works for "FTC" platform. Generate error on other platforms.
#pragma systemFile            // This eliminates warning for "unreferenced" functions

#define MAX_IR_SPEED 30    // Fastest the bot will move while seeking IR emitter
// #define MAX_SPEED 100           // Speed bot moves during sprints
// #define COUNTS_PER_DEGREE 28    // Encoder counts per degree of rotation

// VERSION 2.2



//=============================================================================
// Function: aim()
//
// Description:
//    This function will aim the robot at the IR emitter using the IR seeker
// sector 4 of the IR seeker must be alighed with ball shooter
//
//=============================================================================
bool aim()
{

  bool aimValidate = true;

     while (SensorValue[IR_seeker] != 4)
     {
      if(nPgmTime >  3000)
      {
        aimValidate = false;
        break;
      }

      if(SensorValue[IR_seeker] < 1)
      {
        aimVariable = false;
        break;
      }
      if (SensorValue[IR_seeker] < 4)
      {
        motor[Front_Drive_L] = -MAX_IR_SPEED; // looking from the top, left side moves back, right
        motor[Front_Drive_R] = MAX_IR_SPEED; // side moves forward for CCW rotation
        motor[Rear_Drive_L] = -MAX_IR_SPEED;  // IR emitter is to the left of bot
        motor[Rear_Drive_R] = MAX_IR_SPEED;
      }
      if (SensorValue[IR_seeker] > 4)
      {
        motor[Front_Drive_L] = MAX_IR_SPEED; // looking from the top, left side forward, right
        motor[Front_Drive_R] = -MAX_IR_SPEED; // side moves back for CW rotation
        motor[Rear_Drive_L] = MAX_IR_SPEED; // IR emitter is to the right of bot
        motor[Rear_Drive_R] = -MAX_IR_SPEED;
      }
    } // end of while loop

    motor[Front_Drive_L] = 0; // since we are now pointed at the emitter, stop motors
    motor[Front_Drive_R] = 0; //
    motor[Rear_Drive_L] = 0;
    motor[Rear_Drive_R] = 0;
    wait10Msec(20);  // wait for bot to actually stop turning

    return aimVariable;

}

//-----------------------------------------------------------------------------
//                              End of file
//-----------------------------------------------------------------------------
