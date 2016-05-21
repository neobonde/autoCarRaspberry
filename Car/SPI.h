#pragma once

#include <bcm2835.h>
#include <stdio.h>
#include <iostream>
#include "global.h"

using namespace std;

class SPI{
public:
	SPI();
	void send_read(int8_t* spiOut_, int8_t* spiIn_);	
	
};
