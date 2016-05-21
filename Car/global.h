#pragma once

#include "car.h"
#include "TCP.h"
#include "SPI.h"

extern int8_t spiOut[7];
extern int8_t spiIn[7];

extern car autoCar;
/*
struct dataOut{
	int8_t speed;//-26 to 26 || -13km/h to 13km/h 
	int8_t servo;//-100 to 100 || indicates the angle of the servo 0 is middle 
	int8_t start;//0 Shutdown || 1 Started  
	int8_t key1, key2, key3, key4;//PSoC Sync
};

struct dataIn{
	int8_t tacho;
	int8_t roadL;
	int8_t roadR;
	int8_t dist;
	int8_t bat1;
	int8_t bat2;
	int8_t key1;
};

typedef struct dataOut DataOut;
typedef struct dataIn DataIn;

extern DataIn spiIn;
extern DataOut spiOut;
*/

