/*
 * pressure.cpp
 *
 */ 

#include "pressure.h"
#include "macros.h"

void Pressure() {
	
	char msg[5];	
	int adcvalue = analogRead(PIN_PRESSURE);    // read the analog in value:
	long pressure = 950 + adcvalue / 8.5;  //convert it to milli bars
	
	// RF transmission
	vw_send((uint8_t *)"$", 1);
	vw_wait_tx(); // Wait until the whole message is gone
	vw_send((uint8_t *)"P", 1);
	vw_wait_tx(); // Wait until the whole message is gone
	
	if(pressure<1000) {
		vw_send((uint8_t *)"0", 1);
		vw_wait_tx(); // Wait until the whole message is gone
		dtostrf(pressure, 3, 2, msg);
		vw_send((uint8_t *)msg, strlen(msg));
		vw_wait_tx(); // Wait until the whole message is gone
	}
	else{
		dtostrf(pressure, 3, 2, msg);
		vw_send((uint8_t *)msg, strlen(msg));
		vw_wait_tx(); // Wait until the whole message is gone
	}
	vw_send((uint8_t *)"\r", 1);
	vw_wait_tx(); // Wait until the whole message is gone/*
	
	/*	
	Serial.print("\n>Pressure: ");
	Serial.print(pressure);   // print the pressure
	Serial.println(" mb");
	*/
	
}