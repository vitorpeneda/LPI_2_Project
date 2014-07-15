/*
 * BattLevel.cpp
 *
 */ 
#include "macros.h"
#include "BatteLevel.h"

void Bat_Level() {
	
	int bat_lev = analogRead(PIN_BATT)*5/1024;    // read the analog in value:

	// RF transmission	
	vw_send((uint8_t *)"$", 1);
	vw_wait_tx(); // Wait until the whole message is gone
	if (bat_lev >= 3) { // Battery OK
		
		
		vw_send((uint8_t *)"B1", 3);
		vw_wait_tx(); // Wait until the whole message is gone
	}
	else {
		
		vw_send((uint8_t *)"B0", 3);
		vw_wait_tx(); // Wait until the whole message is gone
	}
	vw_send((uint8_t *)"\r", 1);
	vw_wait_tx(); // Wait until the whole message is gone
	
	vw_send((uint8_t *)"\n", 1);
	vw_wait_tx(); // Wait until the whole message is gone/*
	
}