/*
 * windDirection.cpp
 *
 * Created: 22/05/2014 00:45:27
 *  Author: Vitor
 */ 

#include "macros.h"
#include "windDirection.h"


// ADC readings:
uint8_t adc_table[NUMDIRS] = {23, 46, 72, 116, 159, 197, 223, 237};

// These directions match 1-for-1 with the values in adc, but
// will have to be adjusted as noted above. Modify 'dirOffset'
char *strVals[NUMDIRS] = {"E","SE","S","NE","SW","N","NW","W"};
uint16_t  degree_table[NUMDIRS] = {90, 135, 180, 45, 225, 0, 315, 270};
uint8_t dirOffset=0;

//=======================================================
// Find vane direction.
//=======================================================
void calcWindDir() {
	int val;
	uint8_t x, reading;

	val= analogRead(PIN_WDIR);
	val >>=2;        // Shift to 255 range
	reading = val;

	// Look the reading up in directions table. Find the first value
	// that's >= to what we got.
	for (x=0; x<NUMDIRS; x++) {
		if (adc_table[x] >= reading)
		break;
	}
	
	x = (x + dirOffset) % 8;   // Adjust for orientation
	Serial.print("\n>Wind dir: ");
	Serial.print(strVals[x]);
	Serial.print(" :: ");
	Serial.print(degree_table[x]);
	Serial.print("º");
}

