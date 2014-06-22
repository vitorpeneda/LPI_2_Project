/*
 * macros.h
 *
 * Created: 21/05/2014 01:24:59
 *  Author: Vitor
 */ 


#ifndef MACROS_H_
#define MACROS_H_

#include "Arduino.h"

//General units
#define ENGLISH	1 // wind speed in miles per hour, rain in inches, temperature in degrees Fahrenheit
#define SI		2 // International System, aka the metric system. Wind speed in meters per second, rain in mm, temperature in degrees Celsius

//Pins
#define PIN_TEMP_HUM 4	// Digital 4
#define PIN_RAIN	 3	// Digital 3
#define PIN_WSPEED	 2	// Digital 2
#define STATUSLED	13	// Digital 13
#define PIN_WDIR	 0	// Analog 1
#define BATTLVL		 1	// Analog 2

// How often we want to calculate wind speed or direction
#define MSECS_CALC_WIND_SPEED 5000
#define MSECS_CALC_WIND_DIR   5000
#define MSECS_CALC_RAIN       5000
#define MSECS_CALC_TEMP_HUM	  5000
#define WIND_RPM_TO_MPH		  22.686745; // divide RPM by this for velocity
#define WIND_RPM_TO_MPS		  50.748803; // divide RPM by this for meters per second"
#define ZERODELAY			  4000; // ms, zero RPM if no result for this time period (see ISR below)
#define NUMDIRS				  8

#endif /* MACROS_H_ */