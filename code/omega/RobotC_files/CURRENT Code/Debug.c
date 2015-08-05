#include "JoystickDriver.c";

task main()
{
	disableDiagnosticsDisplay();

	if ( externalBatteryAvg < 0)
  {
  	nxtDisplayTextLine(3, "Ext Batt: OFF");       //External battery is off or not connected
  }
  else
  {
   	nxtDisplayTextLine(3, "Ext Batt:%4.1f V", externalBatteryAvg / (float) 1000);
  }

  nxtDisplayTextLine(4, "NXT Batt:%4.1f V", nAvgBatteryLevel / (float) 1000);   // Display NXT Battery Voltage

  if ((nAvgBatteryLevel / (float) 1000) < 13)
  {


}
