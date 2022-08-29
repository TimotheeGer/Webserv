#ifndef MIMES_HPP
#define MIMES_HPP

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

class Mimes {

    public:

        mimes(void);
        ~mimes(void);


		std::string	getTypes(std::string extension);

    private:

        std::map<std::string, std::string>, ft::comp> mimes_;

};

#endif