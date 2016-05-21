#include <pthread.h>
#include "global.h"


SPI PSoC = SPI();

int8_t spiOut[7] = {0,0,0,-128,-2,128,4};
int8_t spiIn[7];


car autoCar = car();

void* spiThread(void* data){
	while(1){
		spiOut[0] = autoCar.getSpeed();
		spiOut[1] = 5;
		spiOut[2] = autoCar.getRun();
		PSoC.send_read(spiOut,spiIn);
		
		cout << "tacho: " <<static_cast<int>(spiIn[0]) << endl;
		usleep(1000000);
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
	TCP server = TCP(9000);
	
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
