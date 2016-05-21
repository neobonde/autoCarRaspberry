#pragma once

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include "global.h"

using namespace std;

class TCP{
public:
	TCP(int port = 9000);
	void *waitForConnection(void);
	static void* threadWrapper(void *arg);
//	string getCmd();
//	void setCmd(string cmd);
//	bool getInStatus();
//	void changeOutStatus(bool Status);
	void comandToSend(string comandToSend);
	const string readTextTCP(string inText);
	void writeTextTCP(string line);


 private:
	int sockWel;
	int sockNew;
	int portno;
	socklen_t size;
	struct sockaddr_in serv_addr, cli_addr;
	//bool statusIn_, statusOut_;
	string command;



};
