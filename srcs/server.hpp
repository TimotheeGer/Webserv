#ifndef SERVER_HPP
#define SERVER_HPP

#include <algorithm>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <poll.h>
#include <string>
#include <sstream>
#include <iostream>
// #include <string.h>
#include <fstream>
// #include <stdlib.h>

class server {

    public:

        server(void);
        ~server(void);

        int     init_socket(void);
        int     wait_connection(void);
        int     new_socket(void);
        int     get_request(void);
        void    open_file_and_make_bin(void);
        void    make_response(void);
        void    clear_server(void);
        int     send_message(void);
        std::string    error_page();

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
        std::string         _http;
        std::string         _final;
        char*               http;
        std::string         _error_code;
        FILE*               _document;



};

#endif