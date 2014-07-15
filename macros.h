/*
 * macros.h
 *
 */ 


#ifndef MACROS_H_
#define MACROS_H_

#include <Arduino.h>
#include <stdlib.h>
#include "RTClib.h"
#include "Wire.h"
#include "rtc.h"
#include "VirtualWire.h"
#include "pressure.h"
#include "DHT.h"
#include "BatteLevel.h"

//General units
#define SI		2 // International System, aka the metric system. Wind speed in meters per second, rain in mm, temperature in degrees Celsius

//Pins
#define PIN_TEMP_HUM 4	// Digital 4
#define PIN_RAIN	 3	// Digital 3
#define PIN_WSPEED	 2	// Digital 2
#define STATUSLED	13	// Digital 13
#define PIN_WDIR	 0	// Analog 0
#define BATTLVL		 1	// Analog 1
#define PIN_PRESSURE 2	// Analog 2
#define PIN_BATT	 3  // Analog 3

// How often we want to calculate wind speed or direction
#define MSECS_CALC_DATA_TIME	20000
#define MSECS_CALC_WIND_SPEED	20000
#define MSECS_CALC_WIND_DIR		20000
#define MSECS_CALC_RAIN			20000
#define MSECS_CALC_TEMP_HUM		20000
#define MSECS_CALC_PRESSURE	    20000
#define MSECS_CALC_BATT_LEVEL   20000
#define WIND_RPM_TO_MPH		  22.686745; // divide RPM by this for velocity
#define WIND_RPM_TO_MPS		  50.748803; // divide RPM by this for meters per second"
#define ZERODELAY			  4000; // ms, zero RPM if no result for this time period (see ISR below)
#define NUMDIRS				  8

#define RAIN_BUCKETS_TO_INCHES  0.0086206896; // multiply bucket tips by this for inches
#define RAIN_BUCKETS_TO_MM		0.2794;       // multiply bucket tips by this for mm

#endif /* MACROS_H_ */