//=============================================================================
// Function: Start()
//
// Description:
//    This function will skip the waitForStart() function if the left arrow
//    button is pushed within 3 seconds of starting the autonomous program.
//
// Parameters: None
//=============================================================================
void Start()
{
   nNxtButtonTask  = -2;   // Grab control of the buttons. '-3' is invalid for task, so no task will be
   // executed when a button is pressed.
   TButtons nBtn;
   bool skip_wait = false;  // if skip_wait = true, then skip the waitforstart
   ClearTimer(T3);

   while (time1[T3] < 3000) // wait 3 sec for any button press, after that, default to waitforstart
   {
      nBtn = nNxtButtonPressed;
      if (nBtn != -1)
         break;
   }

   skip_wait = ( nBtn == kLeftButton );


   if (skip_wait == false)
      waitForStart(); // Wait for the beginning of autonomous phase.

} // End of Start()

//-----------------------------------------------------------------------------
//                              End of file
//-----------------------------------------------------------------------------
