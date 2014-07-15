/*
 * rtc.cpp
 *
 */ 
#include "macros.h"  

extern RTC_DS1307 rtc;


void Rtc() {
	
	char msg[5];
	DateTime now = rtc.now();
	
	// RF transmission
	
	//Date
	vw_send((uint8_t *)"START\n", 6);
	vw_wait_tx(); // Wait until the whole message is gone
	vw_send((uint8_t *)"$", 1);
	vw_wait_tx(); // Wait until the whole message is gone	
	vw_send((uint8_t *)"D", 1);	
	vw_wait_tx(); // Wait until the whole message is gone	
	itoa(now.year(), msg, 10);
	vw_send((uint8_t *)msg, strlen(msg));
	vw_wait_tx(); // Wait until the whole message is gone
	vw_send((uint8_t *)"-", 1);
	vw_wait_tx(); // Wait until the whole message is gone
	if (now.month()<10)	{
		vw_send((uint8_t *)"0", 1);
		vw_wait_tx(); // Wait until the whole message is gone
		itoa(now.month(), msg, 10);
		vw_send((uint8_t *)msg, strlen(msg));
		vw_wait_tx(); // Wait until the whole message is gone
	} 
	else {
		itoa(now.month(), msg, 10);
		vw_send((uint8_t *)msg, strlen(msg));
		vw_wait_tx(); // Wait until the whole message is gone
	}
	vw_send((uint8_t *)"-", 1);
	vw_wait_tx(); // Wait until the whole message is gone
	if (now.day()<10)	{
		vw_send((uint8_t *)"0", 1);
		vw_wait_tx(); // Wait until the whole message is gone
		itoa(now.day(), msg, 10);
		vw_send((uint8_t *)msg, strlen(msg));
		vw_wait_tx(); // Wait until the whole message is gone
	}
	else {
		itoa(now.day(), msg, 10);
		vw_send((uint8_t *)msg, strlen(msg));
		vw_wait_tx(); // Wait until the whole message is gone
	}
	vw_send((uint8_t *)"\r", 1);
	vw_wait_tx(); // Wait until the whole message is gone/*
	
	// Time
	vw_send((uint8_t *)"$", 1);
	vw_wait_tx(); // Wait until the whole message is gone
	vw_send((uint8_t *)"C", 1);
	vw_wait_tx(); // Wait until the whole message is gone
	if (now.hour()<10)	{
		vw_send((uint8_t *)"0", 1);
		vw_wait_tx(); // Wait until the whole message is gone
		itoa(now.hour(), msg, 10);
		vw_send((uint8_t *)msg, strlen(msg));
		vw_wait_tx(); // Wait until the whole message is gone
	}
	else {
		itoa(now.hour(), msg, 10);
		vw_send((uint8_t *)msg, strlen(msg));
		vw_wait_tx(); // Wait until the whole message is gone
	}
	vw_send((uint8_t *)":", 1);
	vw_wait_tx(); // Wait until the whole message is gone
	if (now.minute()<10) {
		vw_send((uint8_t *)"0", 1);
		vw_wait_tx(); // Wait until the whole message is gone
		itoa(now.minute(), msg, 10);
		vw_send((uint8_t *)msg, strlen(msg));
		vw_wait_tx(); // Wait until the whole message is gone
	}
	else {
		itoa(now.minute(), msg, 10);
		vw_send((uint8_t *)msg, strlen(msg));
		vw_wait_tx(); // Wait until the whole message is gone
	}
	vw_send((uint8_t *)":", 1);
	vw_wait_tx(); // Wait until the whole message is gone
	if (now.second()<10) {
		vw_send((uint8_t *)"0", 1);
		vw_wait_tx(); // Wait until the whole message is gone
		itoa(now.second(), msg, 10);
		vw_send((uint8_t *)msg, strlen(msg));
		vw_wait_tx(); // Wait until the whole message is gone
	}
	else {
		itoa(now.second(), msg, 10);
		vw_send((uint8_t *)msg, strlen(msg));
		vw_wait_tx(); // Wait until the whole message is gone
	}
	vw_send((uint8_t *)"\r", 1);
	vw_wait_tx(); // Wait until the whole message is gone/*
	
	/*	
	Serial.print("\n\n>Date: ");
	Serial.print(now.year(), DEC);
	Serial.print('/');
	Serial.print(now.month(), DEC);
	Serial.print('/');
	Serial.print(now.day(), DEC);
	Serial.print(' ');
	Serial.print(now.hour(), DEC);
	Serial.print(':');
	Serial.print(now.minute(), DEC);
	Serial.print(':');
	Serial.print(now.second(), DEC);
	
	*/
}


