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
#include <string.h>
#include <cstring>
#include <fstream>
#include <stdlib.h>

#define PORT 8080

int main(int argc, char const *argv[])
{
    int server_fd, new_socket; long valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char *bin_image;
    int tailleImage = 0;
    char c_size[10 + sizeof(char)];

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
    
    memset(address.sin_zero, '\0', sizeof address.sin_zero);
    
    // Only this line has been changed. Everything is same.
    char hello [74] = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
    
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("In socket");
        exit(EXIT_FAILURE);
    }
    
    
    
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0)
    {
        perror("In bind");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 10) < 0)
    {
        perror("In listen");
        exit(EXIT_FAILURE);
    }

    std::string content;
    std::string requete;

    while(1)
    {
        printf("\n+++++++ Waiting for new connection ++++++++\n\n");
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
        {
            perror("In accept");
            exit(EXIT_FAILURE);
        }
        
        //reception de la requete 
        char buffer[30000] = {0};
        valread = read( new_socket , buffer, 30000);
        printf("%s\n",buffer );

        //reponse de la requete
        requete.clear();
       
        // FILE* image = fopen("maison.jpg", "rb");
        FILE* image = fopen("info.html", "rb");
    
        fseek(image, 0 ,SEEK_END);
        tailleImage = ftell(image);
        rewind(image);

        char c_size[10 + sizeof(char)];
		std::sprintf(c_size, "%d", tailleImage);

    	bin_image = (char*) malloc (sizeof(char) * tailleImage);
        printf("taille image  = %d\n", tailleImage);
        int res = fread(bin_image, 1, tailleImage, image);
        printf("res = %d\n", res);

 


		// requete = requete + "HTTP/1.1 200 OK\nContent-Type: image/jpeg\nContent-Length: " + c_size + "\n\n";
		requete = requete + "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: " + c_size + "\n\n";
        char *str = (char *)malloc(sizeof(char) * (requete.size() + tailleImage));
        memcpy(str, requete.c_str(), requete.size());
        printf("str = %s\n", str);
        memcpy(str + strlen(str), bin_image, tailleImage);
        write(new_socket , str , requete.size() + tailleImage);
        printf("------------------Hello message sent-------------------");
        close(new_socket);
    }
    return 0;
}