#ifndef SERVER_HPP
#define SERVER_HPP

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

class server {

    public:

        server(void);
        ~server(void);

        int init_socket(void);
        int wait_connection(void);
        int new_socket(void);


    private:

        int                 _server_fd;
        int                 _new_socket;
        long                _valread;
        struct sockaddr_in  _address;
        int                 _addrlen;
        char*               _content_bin;
        long                _content_size;
        char                _c_size[11];
        char                _request[30000];
        uint16_t            _port;
        std::string         _response;
        FILE*               _document;


};

#endif