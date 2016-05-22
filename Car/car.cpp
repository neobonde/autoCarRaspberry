#include "car.h"

#define MIN_DIST 20
#define TURN_CONST 1
#define OVERTAKE_SPEED 6
#define CAR_LENGTH 0.8

car::car(): tmr(){
	run = 0;
	speed = 0;
	leftCount = 0;
	rightCount = 0;
	laneChangeState = 0;
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
string car::status(int _tacho, int _roadL,  int _roadR, int _dist, int _batOne,  int _batTwo ){		
	//5 roadR roadL speed afstand bat1 bat2
	//roadR 0 eller 1
	//roadL 0 eller 1
	//speed xxx første er + eller - de 2 sidste er hastigheden
	//afstand er afstanden i cm, 3 digits
	//bat1 og bat2 er 0 og 0, da de ikke er implementeret.

	cout << _tacho << endl;	
	stringstream output;
	string outputTcp;
	
	char tachoSignPrefix ='+';
	string tachoPrefix="";
	string distPrefix="00" ;
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
	if(_tacho<0){
		tachoSignPrefix ='-';
	}

	if(_tacho<10){
		tachoPrefix ="0";
	}else{
		tachoPrefix ="";
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




	output << "11QstatusQ5" << _roadR << _roadL << tachoSignPrefix << tachoPrefix <<  abs(_tacho) <<distPrefix << _dist << batPrefix1 << _batOne << batPrefix2 << _batTwo  << "W" ;
	return output.str();
}	

void car::setSpeed(int _speed){
	speed = _speed;
};	//Set the speed of the car for the next SPI transaction.

void car::setServo(int _servo){
	servo = _servo;
}

int car::getServo(){
	return servo;
}

int car::getSpeed(){
	return speed;
}

bool car::getRun(){
	return run;
}

void car::setOvertakeFlag(bool flag_){
	overtakeFlag = flag_;
}

bool car::getOvertakeFlag(){
	return overtakeFlag;
}

double car::calcOvertakeTime(float carLength_){
	return (carLength_*3.6)/speed;
}


bool car::laneChangeL(bool infraRight_){
	servo = -100;
	if(infraRight_){
		servo = 20;
		return true;
	}
	return false;	
}

bool car::laneChangeR(bool infraLeft_){
	servo = 100;
	if(infraLeft_){
		servo = -20;
		return true;
	}
	return false;	
}

bool car::overtake(bool infraLeft_, bool infraRight_, int distance_){
	run = 1;
	if(speed == 0){
		speed = OVERTAKE_SPEED;
	}
	switch(laneChangeState){
		case 0:
			if(laneChangeL(infraRight_)){
				laneChangeState = 1;
				overtakeTime = calcOvertakeTime(CAR_LENGTH);
				tmr.reset();
			}
			break;
		case 1:
			if(tmr.elapsed() > overtakeTime){
				laneChangeState = 2;
			}
			followRoad(infraLeft_, infraRight_, distance_);
			
			//wait for 0.8m
				
			break;

		case 2:
			if(laneChangeR(infraLeft_)){
				laneChangeState = 0;
				return 1;
			}
			break;
	}
	return 0;
}


void car::followRoad(bool infraLeft_, bool infraRight_,int distance_){
	if(distance_ < MIN_DIST){
		run = 0;		
		speed = 0;
	}

	if(infraLeft_){
		if(leftCount > -100){
			leftCount --;
		}
		servo = leftCount * TURN_CONST;		
	}else{
		leftCount = 0;	
	}

	if(infraRight_){
		if(rightCount < 100){	
			rightCount ++;
		}
		servo = rightCount * TURN_CONST;		
	}else{
		rightCount = 0;	
	}
}


	void car::setTacho(int tacho_){
		tacho = tacho_;	
	}
	void car::setRoadL(int roadL_){
		roadL = roadL_;
	}
	void car::setRoadR(int roadR_){
		roadR = roadR_;
	}
	void car::setDist(int dist_){
		distance = dist_;
	}
	void car::setBat1(int bat1_){
		batOne = bat1_;
	}
	void car::setBat2(int bat2_){
		batTwo = bat2_;
	}






