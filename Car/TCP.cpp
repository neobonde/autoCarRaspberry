#include "TCP.h"

TCP::TCP(int port)
{
	//statusIn_ = 0;
	//statusOut_ = 0;
	string command;
	portno = port;

	cout << "Setting up TCP server" << endl << "port: " << portno << endl; 

	sockWel = socket(AF_INET, SOCK_STREAM, 0);
	if(sockWel < 0){
		cout << "Error opening socket" << endl;
	}

	cout << "Socket opened" << endl;

	int enable = 1;
	if (setsockopt(sockWel, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
		cout << "Error on resuaddr SO_OPT" << endl;

	cout << "sock SO_REUSEADDR set" << endl;

	if (setsockopt(sockNew, SOL_SOCKET, SO_KEEPALIVE, &enable, sizeof(int)) <0){
		cout << "Error on keepalive SO_OPT" << endl;
	}
	cout << "sock SO_KEEPALIVE set" << endl;

	int keepAlive = 3;
/*	
	if (setsockopt(sockNew, SOL_TCP, TCP_KEEPCNT, &keepAlive, sizeof(int)) <0){
		cout << "Error on keepalive TCP_KEEPCNT" << endl;
	}

	cout << "sock TCP_KEEPCNT set" << endl;

	int idle = 1;

	if (setsockopt(sockNew, SOL_TCP, TCP_KEEPIDLE, &idle, sizeof(int)) <0){
		cout << "Error on keepalive TCP_KEEPIDLE" << endl;
	}

	cout << "sock TCP_KEEPIDLE set" << endl;


	if (setsockopt(sockNew, SOL_TCP, TCP_KEEPINTVL, &idle, sizeof(int)) <0){
		cout << "Error on keepalive TCP_KEEPINTVL" << endl;
	}

	cout << "sock TCP_KEEPINTVL set" << endl;
*/


	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);

	if (bind(sockWel, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
	{
		cout << "Error on binding" << endl;
	}
	cout << "Binded" << endl;

}

void *TCP::waitForConnection(void){
	// Listening
	cout << "Looking for clients..." << endl;
	listen(sockWel, 5);
	size = sizeof(cli_addr);

	sockNew = accept(sockWel, (struct sockaddr *) &cli_addr, &size);
	if (sockNew < 0)
	{
		cout << "Error on accept" << endl;
	}

	cout << "Client Connected" << endl;


	while(1)
	{
		listen(sockNew, 5);
		command = readTextTCP(command);
		cout<<command<<endl;
		if(command.compare("01QstatusW")==0)
		{
			//string statusStr = autoCar.status(spiIn[0], spiIn[1], spiIn[2], spiIn[3], spiIn[4], spiIn[5]);
			string statusStr = autoCar.status(26,1,2,2,99,88);
		
			
			cout << "status: " << statusStr << endl;
			writeTextTCP(statusStr);			
		}
		else if(command.compare("02QoverhalW")==0)
		{
			writeTextTCP("12QoverhalingQ0003W");			
		}
		else if(command.substr(0,13).compare("03QhastighedQ")==0)
		{
			int speedInt = atoi(command.substr(13,3).c_str());
			
			if(speedInt > 26){
				autoCar.setSpeed(26);	
				writeTextTCP("13QhastighedQ2002W");
			}else if(speedInt < -26){
				autoCar.setSpeed(-26);	
				writeTextTCP("13QhastighedQ2002W");
			}else{
				autoCar.setSpeed(speedInt);
				writeTextTCP("13QhastighedQ2001W");	
			}
		}
		else if(command.compare("04QstartW")==0)
		{
			autoCar.start();
			writeTextTCP("14QstartQ111119999W");//FIXME		

		}
		else if(command.compare("05QstopW")==0)
		{
			autoCar.stop();
			writeTextTCP("15QstopQ3001W");
		}
		else if(command.compare("06QtestW")==0)
		{
			writeTextTCP("16QtestW");
				
		}


		command.clear();
	}

	
	return 0;
}

void *TCP::threadWrapper(void* arg){
	return ((TCP *)arg)->waitForConnection();

}


const string TCP::readTextTCP(string inText)
{
	char ch;
	if(read(sockNew, &ch, 1) == -1){
		cout << "Error on read - Terminating" << endl;
		exit(1);
	}
	while(ch != 0)
	{
		inText += ch;
		read(sockNew, &ch, 1);
	}
	return inText;
}

/**
 * Skriver en tekststreng til en socket med 0 terminering
 *
 * @param outToServer Stream hvortil der skrives data til socket
 * @param line Teksten der skal skrives til socket
 */
void TCP::writeTextTCP(string line)
{
	write(sockNew, line.c_str(), line.length());
	write(sockNew, "\0", 1);
	command.clear();
}

