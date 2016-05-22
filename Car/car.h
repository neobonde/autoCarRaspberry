#pragma once

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <stdint.h>
#include <cstdlib> 
#include <ctime>
#include "timer.hpp"

using namespace std; 

class car{ 
public:
	car();
	int speed10(int8_t spiSpeed);			//returns the speed x10 the actual speed
	float speedFloat(int8_t spiSpeed);		//returns the actual speed as a float in 0.5 km/h increments 
	int distanceConv(int8_t spiDist);		//Return the actual distance in cm
	bool infraLeft(int8_t spiInfraLeft);
	bool infraRight(int8_t spiInfraRight);		//Just convert 0 and 1 to bool?
	int batOneFunc(int8_t spiBatOne);		//Not implemented in hardware discard result
	int batTwoFunc(int8_t spiBatTwo);		//Not implemented in hardware discard result

	void start(); 					//Turns on the lights, sets run to true. Runs startup test.
	void stop();					//Turns off the lights, sets run to false.
	string status(int _speed, int _roadL,  int _roadR, int _dist, int _batOne,  int _batTwo );
	
	void setSpeed(int _speed);			//Set the speed of the car for the next SPI transaction.
	int getSpeed();
	bool getRun();
	void setServo(int _servo);
	int getServo();

	void setOvertakeFlag(bool flag_ = true);	
	bool getOvertakeFlag();	

	double calcOvertakeTime(float carLength_);
	void followRoad(bool infraLeft_, bool infraRight_,int distance_);
	bool laneChangeL(bool infraRight_);
	bool laneChangeR(bool infraLeft_);
	bool overtake(bool infraLeft_, bool infraRight_, int distance_); 				//Overtakes the car in front. 


	void setTacho(int tacho_);
	void setRoadL(int roadL_);
	void setRoadR(int roadR_);
	void setDist(int dist_);
	void setBat1(int bat1_);
	void setBat2(int bat2_);

private:
	int8_t run;
	int8_t speed;
	int8_t servo;

	int leftCount;
	int rightCount;

	int laneChangeState;
	Timer tmr;
	double t;
	double overtakeTime;
	bool overtakeFlag;
	
	int8_t tacho;	
	int8_t roadL;
	int8_t roadR;
	int8_t distance;
	int8_t batOne;
	int8_t batTwo;

};
