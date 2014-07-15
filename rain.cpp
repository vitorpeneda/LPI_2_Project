/*
 * rain.cpp
 *
 */ 

#include "rain.h"
#include "macros.h"

extern int general_units;


float WM_rainfall; // =0;

//Volatiles are subject to modification by ISRs
volatile unsigned long raintime, rainpulsetime, rainpulseinterval, rain;
volatile bool rainstate;

//Constant conversion factors


extern RTC_DS1307 rtc;

void Rain() {
	
	char msg[5];
	DateTime now = rtc.now();
	
	// rainfall unit conversion

	WM_rainfall = rain * RAIN_BUCKETS_TO_MM;
	
	/*Colocar a zero apos mudança de cada dia */
	
	if (now.hour() == 0) {
		Serial.print(now.hour(), DEC);
		Serial.print(':');
		Serial.print(now.minute(), DEC);
		rain=0;
	}
	
	// RF transmission
	vw_send((uint8_t *)"$", 1);
	vw_wait_tx(); // Wait until the whole message is gone
	vw_send((uint8_t *)"R", 1);
	vw_wait_tx(); // Wait until the whole message is gone
	
	if (WM_rainfall<10)	{
		vw_send((uint8_t *)"00", 2);
		vw_wait_tx(); // Wait until the whole message is gone
		dtostrf(WM_rainfall, 2, 2, msg);
		vw_send((uint8_t *)msg, strlen(msg));
		vw_wait_tx(); // Wait until the whole message is gone
	}
	else if(WM_rainfall<100) {
		vw_send((uint8_t *)"0", 1);
		vw_wait_tx(); // Wait until the whole message is gone
		dtostrf(WM_rainfall, 2, 2, msg);
		vw_send((uint8_t *)msg, strlen(msg));
		vw_wait_tx(); // Wait until the whole message is gone
	}
	else{
		dtostrf(WM_rainfall, 2, 2, msg);
		vw_send((uint8_t *)msg, strlen(msg));
		vw_wait_tx(); // Wait until the whole message is gone
	}
	vw_send((uint8_t *)"\r", 1);
	vw_wait_tx(); // Wait until the whole message is gone/*
	
	/*	
	Serial.print("\n>Rainfall: ");
	Serial.print(WM_rainfall,2);
	Serial.print(" mm ");
	*/
}

// interrupt routines (these are called by the hardware interrupts, not by the main code)

void Rain_ISR()
// if the Weather Meters are attached, count rain gauge bucket tips as they occur
// activated by the magnet and reed switch in the rain gauge, attached to input D3
{
	if (digitalRead(PIN_RAIN) == LOW) {
		if (!rainstate) {
			rainstate     = true;
			rainpulsetime = micros();
		}
	}
	else if (rainstate) {
		raintime = micros();
		if (raintime < rainpulsetime) {
			rainpulseinterval = 0xfffffffful - rainpulsetime + raintime; // force positive value
		}
		else {
			rainpulseinterval = raintime - rainpulsetime;
		}
		if (rainpulseinterval > 10000) { //Veriry 10ms debouncing
			rain++;
			rainstate = false;
		}
	}
	else {
		rainstate = false;
	}
}
