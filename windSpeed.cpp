/*
 * windSpeed.cpp
 *
 */ 

#include "windSpeed.h"
#include "macros.h"

extern int general_units;

//Global variables
extern float WM_wspeed;
extern unsigned int windRPM;

//Volatiles are subject to modification by ISRs
extern volatile unsigned long tempwindRPM, windtime, windlast, windinterval;
extern volatile unsigned char windintcount;
extern volatile boolean gotwspeed;

void WSpeed_ISR()
// if the Weather Meters are attached, measure anemometer RPM (2 ticks per rotation), set flag if RPM is updated
// activated by the magnet in the anemometer (2 ticks per rotation), attached to input D3

// this routine measures RPM by measuring the time between anemometer pulses
// windintcount is the number of pulses we've measured - we need two to measure one full rotation (eliminates any bias between the position of the two magnets)
// when windintcount is 2, we can calculate the RPM based on the total time from when we got the first pulse
// note that this routine still needs an outside mechanism to zero the RPM if the anemometer is stopped (no pulses occur within a given period of time)
{
	windtime = micros(); // grab current time

	if ((windintcount == 0) || ((windtime - windlast) > 10000)) // ignore switch-bounce glitches less than 10ms after the reed switch closes
	{
		
		if (windintcount == 0) // if we're starting a new measurement, reset the interval
		windinterval = 0;
		else
		windinterval += (windtime - windlast); // otherwise, add current interval to the interval timer
		if (windintcount == 2) // we have two measurements (one full rotation), so calculate result and start a new measurement
		{
			tempwindRPM = (60000000ul / windinterval); // calculate RPM (temporary since it may change unexpectedly)
			
			windintcount = 0;
			windinterval = 0;
			gotwspeed = true; // set flag for main loop
		}
		windintcount++;
		windlast = windtime; // save the current time so that we can calculate the interval between now and the next interrupt
	}
}


void WSpeed() {
	
	char msg[5];
	
	// windspeed unit conversion
	
	WM_wspeed = float(windRPM) / WIND_RPM_TO_MPS;	
	windRPM = 0;
	windintcount = 0;
	
	// RF transmission
	vw_send((uint8_t *)"$", 1);
	vw_wait_tx(); // Wait until the whole message is gone
	vw_send((uint8_t *)"S", 1);
	vw_wait_tx(); // Wait until the whole message is gone
	
	if (WM_wspeed<10)	{
		vw_send((uint8_t *)"00", 2);
		vw_wait_tx(); // Wait until the whole message is gone
		dtostrf(WM_wspeed, 3, 2, msg);
		vw_send((uint8_t *)msg, strlen(msg));
		vw_wait_tx(); // Wait until the whole message is gone
	} 
	else if(WM_wspeed<100) {
		vw_send((uint8_t *)"0", 1);
		vw_wait_tx(); // Wait until the whole message is gone
		dtostrf(WM_wspeed, 3, 2, msg);
		vw_send((uint8_t *)msg, strlen(msg));
		vw_wait_tx(); // Wait until the whole message is gone
	}
	else{
	dtostrf(WM_wspeed, 3, 2, msg);
	vw_send((uint8_t *)msg, strlen(msg));
	vw_wait_tx(); // Wait until the whole message is gone
	}
	vw_send((uint8_t *)"\r", 1);
	vw_wait_tx(); // Wait until the whole message is gone/*
	
	/*
	Serial.print("\n>Wind speed: ");
	Serial.print(WM_wspeed,2);
	Serial.print(" m/s ");
	*/
}