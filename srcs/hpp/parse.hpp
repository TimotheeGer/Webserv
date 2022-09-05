#ifndef PARSE_HPP
#define PARSE_HPP

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
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "color.hpp"

class Parse {

	public:

		Parse();
		~Parse();

		int parse_request(std::string request, std::map<std::string, std::string> &map_req);

	private:
	
		std::vector<std::string> split_in_tabs(std::string request, std::string del, std::vector<std::string> &tab);
		std::string get_request(std::string word, std::string c, int x);
		std::string get_method_parse(std::vector<std::string> &request);
		
		std::vector<std::string> tab_request;
		std::vector<std::string> tab_get;

};

#endif
