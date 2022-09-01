#include "../hpp/color.hpp"
#include "../hpp/server.hpp"

// ************************************************************************** //
//                               member fonction                          	  //
// ************************************************************************** //

int server::init_socket(void) {

	std::cout << C_CYAN << "\n- init socket -\n" << C_RESET << std::endl;

	if ((this->_server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("In socket");
        return(EXIT_FAILURE);
    }
    if (bind(this->_server_fd, (struct sockaddr *)&this->_address, sizeof(this->_address))<0)
    {
        perror("In bind");
        return(EXIT_FAILURE);
    }
    if (listen(this->_server_fd, 10) < 0)
    {
        perror("In listen");
        return(EXIT_FAILURE);
    }
	return(EXIT_SUCCESS);
};

int server::new_socket(void) {
	
	if ((this->_new_socket = accept(this->_server_fd, (struct sockaddr *)&this->_address, (socklen_t*)&this->_addrlen))<0)
    {
        perror("In accept");
        return(EXIT_FAILURE);
    }
	return(EXIT_SUCCESS);
}