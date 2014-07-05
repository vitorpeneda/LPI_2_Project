/*
 * tempHum.cpp
 *
 * Created: 24/05/2014 16:21:03
 *  Author: Vitor
 */ 

#include "macros.h"
#include "tempHum.h"
#include <DHT.h>

extern float hum;
extern float temp;

DHT dht(PIN_TEMP_HUM, DHT22);


void Temp_Hum() {
	
	char msg[12];
	hum = dht.readHumidity();
	temp = dht.readTemperature();
	
	// check if returns are valid, if they are NaN (not a number) then something went wrong!
	if (isnan(temp) || isnan(hum)) {
		Serial.println("Failed to read from DHT");
		} else {
			
		// RF transmission
		vw_send((uint8_t *)"$", 1);
		vw_wait_tx(); // Wait until the whole message is gone
		vw_send((uint8_t *)"H", 1);
		vw_wait_tx(); // Wait until the whole message is gone
		dtostrf(hum, 2, 1, msg);
		vw_send((uint8_t *)msg, strlen(msg));
		vw_wait_tx(); // Wait until the whole message is gone
		vw_send((uint8_t *)"$", 1);
		vw_wait_tx(); // Wait until the whole message is gone
		vw_send((uint8_t *)"T", 1);
		vw_wait_tx(); // Wait until the whole message is gone
		dtostrf(temp, 2, 1, msg);
		vw_send((uint8_t *)msg, strlen(msg));
		vw_wait_tx(); // Wait until the whole message is gone
		vw_send((uint8_t *)"\r", 1);
			
		
		Serial.print("\n>Humidity: ");
		Serial.print(hum);
		Serial.print(" %\t");
		Serial.print("\n>Temperature: ");
		Serial.print(temp);
		Serial.println(" ºC");
	}
}


