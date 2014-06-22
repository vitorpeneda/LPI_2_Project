/*
 * weather_station_lpi2.cpp
 *
 * Created: 12/05/2014 18:13:28
 *
 *  Author: Eng. Vitor Peneda
 */ 

#include "macros.h"
#include "rain.h"
#include "windSpeed.h"
#include "windDirection.h"
#include "tempHum.h"
//#include "DHT.h"



//Global variables
int general_units = SI;

float temp = 0.0;
float hum = 0.0;

float WM_wdirection = 0;
uint8_t sample_rate = 2; // sample rate (seconds per sample, 0 for as fast as possible)
uint16_t adc = 0;

float WM_wspeed = 0.0;
unsigned int windRPM = 0.0;

//Volatiles are subject to modification by ISRs
volatile unsigned long tempwindRPM, windtime, windlast, windinterval;
volatile unsigned char windintcount = 0;
volatile boolean gotwspeed = false;


unsigned long nextCalcSpeed;   // When we next calc the wind speed
unsigned long nextCalcDir;     // When we next calc the direction
unsigned long nextCalcRain;    // When we next calc the rain
unsigned long nextCalcTemp_Hum;// When we next calc the temperature and humidity relative 

//=======================================================
// Initialize
//=======================================================

void setup() {
  
  Serial.begin(9600);
  
  pinMode(PIN_RAIN,INPUT);			// input from wind meters rain gauge sensor
  digitalWrite(PIN_RAIN,HIGH);		// turn on pullup
  attachInterrupt(1, Rain_ISR, CHANGE);
  
  pinMode(PIN_WSPEED, INPUT);		// input from wind meters windspeed sensor
  digitalWrite(PIN_WSPEED, HIGH);	// turn on pullup
  attachInterrupt(0, WSpeed_ISR, FALLING);
  
  pinMode(PIN_TEMP_HUM, INPUT);		// input from wind meters temp. and hum. sensor
  digitalWrite(PIN_TEMP_HUM, HIGH); // turn on pullup
  
  pinMode(STATUSLED,OUTPUT);		// output to status LED
    
  // turn on interrupts
  interrupts();

  nextCalcSpeed		= millis() + MSECS_CALC_WIND_SPEED;
  nextCalcDir		= millis() + MSECS_CALC_WIND_DIR;
  nextCalcRain		= millis() + MSECS_CALC_RAIN;	
  nextCalcTemp_Hum  = millis() + MSECS_CALC_TEMP_HUM;
  
}


//=======================================================
// Main loop.
//=======================================================
void loop() {
	
	static long templong, windstopped;
	static unsigned long loopstart, loopend;

// record current time so we can sample at regular intervals
	loopstart = millis();
	loopend = loopstart + (sample_rate * 1000ul);
  
	if (loopstart >= nextCalcSpeed) {
		// Blink LED 
		digitalWrite(STATUSLED,HIGH);
		delay(100);
		digitalWrite(STATUSLED,LOW);
		delay(250); 
		
		if (gotwspeed==true){
		
			gotwspeed = false;
			windRPM = word(tempwindRPM);		// grab the RPM value calculated by the interrupt routine
			windstopped = millis() + ZERODELAY; // save this timestamp
		}
		nextCalcSpeed = loopstart + MSECS_CALC_WIND_SPEED; 
		WSpeed();
	}
	
	if (loopstart >= nextCalcDir) {
      calcWindDir();
      nextCalcDir = loopstart + MSECS_CALC_WIND_DIR;
	}
	if (loopstart >= nextCalcRain) {
      Rain();
      nextCalcRain = loopstart + MSECS_CALC_RAIN;
	}
	 
	if (loopstart >=  nextCalcTemp_Hum) {
	 Temp_Hum();
	 nextCalcTemp_Hum = loopstart + MSECS_CALC_TEMP_HUM;
	}
} 
