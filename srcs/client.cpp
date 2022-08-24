#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <algorithm>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <poll.h>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <sstream>
#include <iostream>

int main(int argc, char **argv) {

	int sock = 0;
	long valread;
	struct sockaddr_in serv_addr;
	
	std::string str = "He poto";
	char buffer[1024] = {0};
	// std::cout << "Coucou" << std::endl;

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		std::cout << "Socker Creation Error" << std::endl;
		return -1;
	}
	memset(&serv_addr, '0', sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(8080);

	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
	{
		std::cout << "Invalid Address" << std::endl;
		return -1;
	}

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		std::cout << "Connection Failed" << std::endl;
		return -1;
	}

	send(sock, str.c_str(), str.size(), 0);

	// std::cout << "Hello" << std::endl;

	valread = read(sock , buffer, 1024);
	// std::cout << buffer << std::endl;
	return 0;


}