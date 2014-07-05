/*
 * rtc.cpp
 *
 * Created: 23/06/2014 15:37:48
 *  Author: Vitor
 */ 
#include "macros.h"  

extern RTC_DS1307 rtc;

void Rtc() {
	
	char msg[12];
	DateTime now = rtc.now();
	
	// RF transmission
	vw_send((uint8_t *)"$", 1);
	vw_wait_tx(); // Wait until the whole message is gone	
	vw_send((uint8_t *)"D", 1);	
	vw_wait_tx(); // Wait until the whole message is gone	
	itoa(now.year(), msg, 10);
	vw_send((uint8_t *)msg, strlen(msg));
	vw_wait_tx(); // Wait until the whole message is gone
	vw_send((uint8_t *)"/", 1);
	itoa(now.month(), msg, 10);
	vw_send((uint8_t *)msg, strlen(msg));
	vw_wait_tx(); // Wait until the whole message is gone
	vw_send((uint8_t *)"/", 1);
	itoa(now.day(), msg, 10);
	vw_send((uint8_t *)msg, strlen(msg));
	vw_wait_tx(); // Wait until the whole message is gone
	vw_send((uint8_t *)" ", 1);
	itoa(now.hour(), msg, 10);
	vw_send((uint8_t *)msg, strlen(msg));
	vw_wait_tx(); // Wait until the whole message is gone
	vw_send((uint8_t *)":", 1);
	itoa(now.minute(), msg, 10);
	vw_send((uint8_t *)msg, strlen(msg));
	vw_wait_tx(); // Wait until the whole message is gone
	vw_send((uint8_t *)":", 1);
	itoa(now.second(), msg, 10);
	vw_send((uint8_t *)msg, strlen(msg));
	vw_wait_tx(); // Wait until the whole message is gone/*
	vw_send((uint8_t *)"\r", 1);
	vw_wait_tx(); // Wait until the whole message is gone/*
	
		
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
	

}


