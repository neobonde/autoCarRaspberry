#include "car.h"


car::car(){
	run = 0;
	speed = 0;
}

int car::speed10(int8_t spiSpeed){
	return 5*spiSpeed; // 10/2 = 5
}

float car::speedFloat(int8_t spiSpeed){
	return spiSpeed/2;
}

int car::distanceConv(int8_t spiDist){
	int distance;
	if(spiDist >= 128){
		return 127-(~spiDist+1);
	}else{
		return 128+spiDist;
	}
}

bool car::infraLeft(int8_t spiLeft){
	return spiLeft;
}

bool car::infraRight(int8_t spiRight){
	return spiRight;
}

int batOneFunc(int8_t spiBatOne){
	return -1;
}

int batTwoFunc(int8_t spiBatTwo){
	return -1;
}


void car::start(){
      
	run = 1;	

} 		//Turns on the lights, sets run to true. Runs startup test.
void car::stop(){
	run = 0;
}		//Turns off the lights, sets run to false.
string car::status(int _speed, int _roadL,  int _roadR, int _dist, int _batOne,  int _batTwo ){		
	//5 roadR roadL speed afstand bat1 bat2
	//roadR 0 eller 1
	//roadL 0 eller 1
	//speed xxx første er + eller - de 2 sidste er hastigheden
	//afstand er afstanden i cm, 3 digits
	//bat1 og bat2 er 0 og 0, da de ikke er implementeret.

	cout << _speed << endl;	
	stringstream output;
	string outputTcp;
	
	char spdSignPrefix ='+';
	string distPrefix="00" ;
	string spdPrefix="";
	string batPrefix1, batPrefix2;
	if(_dist<10){
		distPrefix="00";
	}
	else if(_dist<100){
		distPrefix='0';
	}
	else{
		distPrefix="";
	}
	if(_speed<0){
		spdSignPrefix ='-';
	}

	if(_speed<10){
		spdPrefix ="0";
	}else{
		spdPrefix ="";
	}

	if(_batOne<10){
		batPrefix1 ="0";
	}else{
		batPrefix1 ="";
	}

	if(_batTwo<10){
		batPrefix2 ="0";
	}else{
		batPrefix2 ="";
	}




	output << "11QstatusQ5" << _roadR << _roadL << spdSignPrefix << spdPrefix <<  abs(_speed) <<distPrefix << _dist << batPrefix1 << _batOne << batPrefix2 << _batTwo  << "W" ;
	return output.str();
}	

void car::setSpeed(int _speed){
	speed = _speed;
};	//Set the speed of the car for the next SPI transaction.

int car::getSpeed(){
	return speed;
}


void car::overtake(){} 


bool car::getRun(){
	return run;
}









