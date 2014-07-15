/*
 * tempHum.cpp
 *
 */ 

#include "macros.h"
#include "tempHum.h"


extern float hum;
extern float temp;

DHT dht(PIN_TEMP_HUM, DHT22);

void Temp_Hum() {
	
	char msg[5];
	hum = dht.readHumidity();
	delay(1000);
	temp = dht.readTemperature();
	
	// check if returns are valid, if they are NaN (not a number) then something went wrong!
	if (isnan(temp) || isnan(hum)) {
		Serial.println("Failed to read from DHT");
		} else {
			
		// RF transmission
		
		//Humidity
	
		vw_send((uint8_t *)"$", 1);
		vw_wait_tx(); // Wait until the whole message is gone
		vw_send((uint8_t *)"H", 1);
		vw_wait_tx(); // Wait until the whole message is gone
		
		if (hum < 10) {
			vw_send((uint8_t *)"00", 2);
			vw_wait_tx(); // Wait until the whole message is gone
			dtostrf(hum, 2, 2, msg);
			vw_send((uint8_t *)msg, strlen(msg));
			vw_wait_tx(); // Wait until the whole message is gone
		}
		else if(hum<100) {
			vw_send((uint8_t *)"0", 1);
			vw_wait_tx(); // Wait until the whole message is gone
			dtostrf(hum, 2, 2, msg);
			vw_send((uint8_t *)msg, strlen(msg));
			vw_wait_tx(); // Wait until the whole message is gone
		}
		else {
			dtostrf(hum, 2, 2, msg);
			vw_send((uint8_t *)msg, strlen(msg));
			vw_wait_tx(); // Wait until the whole message is gone
		}
		vw_send((uint8_t *)"\r", 1);
		vw_wait_tx(); // Wait until the whole message is gone
		
		// Temperature
		
		vw_send((uint8_t *)"$", 1);
		vw_wait_tx(); // Wait until the whole message is gone
		vw_send((uint8_t *)"T", 1);
		vw_wait_tx(); // Wait until the whole message is gone		
		if (temp<0)	{
			vw_send((uint8_t *)"-", 1);
			vw_wait_tx(); // Wait until the whole message is gone
		} 
		else {
			vw_send((uint8_t *)"+", 1);
			vw_wait_tx(); // Wait until the whole message is gone
		}
		if (temp < 10) {
			vw_send((uint8_t *)"00", 2);
			vw_wait_tx(); // Wait until the whole message is gone
			dtostrf(temp, 3, 2, msg);
			vw_send((uint8_t *)msg, strlen(msg));
			vw_wait_tx(); // Wait until the whole message is gone
		}
		else if(temp<100) {
			vw_send((uint8_t *)"0", 1);
			vw_wait_tx(); // Wait until the whole message is gone
			dtostrf(temp, 3, 2, msg);
			vw_send((uint8_t *)msg, strlen(msg));
			vw_wait_tx(); // Wait until the whole message is gone
		}
		else {
			dtostrf(temp, 3, 2, msg);
			vw_send((uint8_t *)msg, strlen(msg));
			vw_wait_tx(); // Wait until the whole message is gone
		}
		vw_send((uint8_t *)"\r", 1);
		vw_wait_tx(); // Wait until the whole message is gone
					
		/*
		Serial.print("\n>Humidity: ");
		Serial.print(hum);
		Serial.print(" %\t");
		Serial.print("\n>Temperature: ");
		Serial.print(temp);
		Serial.println(" ºC");
		*/
	}
}


