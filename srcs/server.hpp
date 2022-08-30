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
#include <ostream>
// #include <string.h>
#include <fstream>
// #include <stdlib.h>
#include "parse.hpp"
#include "mimes.hpp"

class server {

    public:

        server(void);
        ~server(void);
		
		Parse	parse_r;
		mimes	mimes_r;

        int     init_socket(void);
        int     wait_connection(void);
        int     new_socket(void);
        int     get_request(void);
        int    	open_basics_files(void);
        int    	make_response(void);
        void    clear_server(void);
        int     send_message(void);
		std::string write_response(void);
        std::string    error_page();

    private:

        int                 _server_fd;
        int                 _new_socket;
        long                _valread;
        struct sockaddr_in  _address;
        int                 _addrlen;
        char*               _content_bin;
        long                _content_size;
		char*               _content_bin_two;
        long                _content_size_two;
        char                _c_size[11];
        char                _request[30000];
        uint16_t            _port;
        std::string         _response;
        std::string         _response_two;
        std::string         _http;
        std::string         _final;
        char*               http;
		std::string			code;
		int					code_test;
        char*               http_two;
        std::string         _error_code;
        FILE*               _document;
		std::string 		request_string;
		std::string			GET;
		std::string			Host;
		std::string			Accept;
		std::map<std::string, std::string> map_serv;
		std::map<int, std::string> map_code;



};

#endif