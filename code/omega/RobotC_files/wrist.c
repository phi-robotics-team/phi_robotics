//=============================================================================
// Function: Wrist()
//
// Description:
//    This function will move the wrist the degrees specified in "degrees".
//
//    The following are the home position counts of the servos:
//    Left servo = 0
//    Right servo = 255
//
// Parameters: degrees = degrees to rotate wrist
//=============================================================================
void Wrist( float degrees )
{
   const float COUNTS_PER_DEG = 2.05;
   const float MAX_COUNTS = 255;
   const float MIN_COUNTS = 0;
   int countDistance;

   // Calculate the degrees to travel in servo counts
   countDistance = ( int )(degrees * COUNTS_PER_DEG);

   // If the counts are in range, then add the values to the servos.
   // Should just need to check the left servo.
   if( ((ServoValue[L_Wrist] + countDistance) < MAX_COUNTS) && ((ServoValue[L_Wrist] + countDistance) >= MIN_COUNTS))
   {
      ServoValue[L_Wrist] += countDistance;
      ServoValue[R_Wrist] += -countDistance;
   }
   

} // End of Move()

//-----------------------------------------------------------------------------
//                              End of file
//-----------------------------------------------------------------------------
