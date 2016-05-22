#include <pthread.h>
#include "global.h"


SPI PSoC = SPI();

int8_t spiOut[7] = {0,0,0,-128,-2,128,4};
int8_t spiIn[7];


car autoCar = car();
TCP server = TCP(9000);



void* spiThread(void* data){
	while(1){
		
		if( autoCar.getRun() == true)
		{
			if( autoCar.getOvertakeFlag() == false)
			{
				autoCar.followRoad(spiIn[1],spiIn[2],spiIn[3]); //insert paramteres
			}else if( autoCar.getOvertakeFlag() == true)
			{
				if(autoCar.overtake(spiIn[1],spiIn[2],spiIn[3])) 
				{ //insert parameters
					autoCar.setOvertakeFlag(false);
					server.writeTextTCP("12QoverhalingQ0001W");			
				}
			}
		}

		spiOut[0] = autoCar.getSpeed();
		spiOut[1] = autoCar.getServo();
		spiOut[2] = autoCar.getRun();
	
		PSoC.send_read(spiOut,spiIn);
		
		autoCar.setTacho(spiIn[1]);
		autoCar.setRoadL(spiIn[2]);
		autoCar.setRoadR(spiIn[3]);
		autoCar.setDist(spiIn[4]);
		autoCar.setBat1(spiIn[5]);
		autoCar.setBat2(spiIn[6]);

		usleep(100000);
	}
}

int main(){

	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);

	pthread_t TCPserver;
	pthread_t SPImaster;
	int err;
	string besked;
	
	err = pthread_create(&TCPserver,&attr,&TCP::threadWrapper,&server);	
	if(err !=0){
		cout << "Thread create error TCPserver!" << endl;

	}
	
	err = pthread_create(&SPImaster,&attr,spiThread,NULL);	
	if(err !=0){
		cout << "Thread create error TCPserver!" << endl;

	}
	

	string tmp;
	while(1);
	

    return 0;
}
