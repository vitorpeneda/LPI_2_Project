/*
 * pressure.cpp
 *
 * Created: 04/07/2014 22:36:24
 *  Author: Vitor
 */ 

#include "pressure.h"
#include "macros.h"

void Pressure() {
	
	char msg[12];	
	int adcvalue = analogRead(PIN_PRESSURE);    // read the analog in value:
	long pressure = 950 + adcvalue / 8.5;  //convert it to milli bars
	
	// RF transmission
	vw_send((uint8_t *)"$", 1);
	vw_wait_tx(); // Wait until the whole message is gone
	vw_send((uint8_t *)"P", 1);
	vw_wait_tx(); // Wait until the whole message is gone
	dtostrf(pressure, 2, 1, msg);
	vw_send((uint8_t *)msg, strlen(msg));
	vw_wait_tx(); // Wait until the whole message is gone
	vw_send((uint8_t *)"\r", 1);
	vw_wait_tx(); // Wait until the whole message is gone/*
	
	vw_send((uint8_t *)"\n", 1);
	vw_wait_tx(); // Wait until the whole message is gone/*
	
	Serial.print(">Pressure: ");
	Serial.print(pressure);   // print the pressure
	Serial.println(" mb");
	
	
}