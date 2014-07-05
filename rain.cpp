/*
 * rain.cpp
 *
 * Created: 21/05/2014 01:22:48
 *  Author: Vitor
 */ 

#include "rain.h"
#include "macros.h"

extern int general_units;


float WM_rainfall; // =0;

//Volatiles are subject to modification by ISRs
volatile unsigned long raintime, rainpulsetime, rainpulseinterval, rain;
volatile bool rainstate;

//Constant conversion factors
const float RAIN_BUCKETS_TO_INCHES = 0.0086206896; // multiply bucket tips by this for inches
const float RAIN_BUCKETS_TO_MM = 0.2794;       // multiply bucket tips by this for mm


void Rain() {
	
	char msg[12];
	
	// rainfall unit conversion
	switch (general_units) {
		case SI: // mm
		WM_rainfall = rain * RAIN_BUCKETS_TO_MM;
		break;
		case ENGLISH: // inches
		WM_rainfall = rain * RAIN_BUCKETS_TO_INCHES;
		break;
		default:
		WM_rainfall = -1.0; // error, invalid units
	}
	
	//Colocar a zero apos mudança de cada dia
	
	// RF transmission
	vw_send((uint8_t *)"$", 1);
	vw_wait_tx(); // Wait until the whole message is gone
	vw_send((uint8_t *)"R", 1);
	vw_wait_tx(); // Wait until the whole message is gone
	dtostrf(WM_rainfall, 2, 1, msg);
	vw_send((uint8_t *)msg, strlen(msg));
	vw_wait_tx(); // Wait until the whole message is gone
	vw_send((uint8_t *)"\r", 1);
	vw_wait_tx(); // Wait until the whole message is gone/*
	
	
	Serial.print("\n>Rainfall: ");
	
	switch (general_units) // change decimal point for different units
	{
		case ENGLISH:
		Serial.print(WM_rainfall,2);
		Serial.print(" inches ");
		break;
		case SI:
		Serial.print(WM_rainfall,2);
		Serial.print(" mm ");
		break;
	}
	
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
