#include "color.hpp"
#include "server.hpp"

// ************************************************************************** //
//                               Constructor                             	  //
// ************************************************************************** //

server::server(void) { 
		
	std::cout << C_GREEN << "\n- Launch Server -        \n" << C_RESET << std::endl;
	
	this->_addrlen = sizeof(this->_address);
	this->_port = 8080;
	this->_address.sin_family = AF_INET;
    this->_address.sin_addr.s_addr = INADDR_ANY;
    this->_address.sin_port = htons( this->_port );
    
	memset(this->_address.sin_zero, '\0', sizeof(this->_address.sin_zero));
	memset(this->_c_size, '\0', sizeof(this->_c_size));
	memset(this->_request, '\0', sizeof(this->_request));
	
	return;
};

server::~server(void) { return; };

// ************************************************************************** //
//                               member fonction                          	  //
// ************************************************************************** //

int server::init_socket(void) {

	std::cout << C_CYAN << "\n- init socket -         \n" << C_RESET << std::endl;

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

int server::wait_connection(void) {

	while(1)
	{

		std::cout << C_BLUE << "\n- Waiting for new connection -         \n" << C_RESET << std::endl;
		
		if ((this->_new_socket = accept(this->_server_fd, (struct sockaddr *)&this->_address, (socklen_t*)&this->_addrlen))<0)
    	{
    	    perror("In accept");
    	    return(EXIT_FAILURE);
    	}
		// new_socket();

    	this->_valread = read( this->_new_socket , this->_request, 30000);
		std::cout << this->_request << std::endl;

		this->_response.clear();
		
		//////////////////////////////////////////////////////////////////////////////////////
		// open file
		// FILE* image = fopen("maison.jpg", "rb");
        this->_document = fopen("info.html", "rb");
		// get size of file
        fseek(this->_document, 0 ,SEEK_END);
        this->_content_size = ftell(this->_document);
        rewind(this->_document);
		std::sprintf(this->_c_size, "%ld", this->_content_size);


    	this->_content_bin = (char*) malloc (sizeof(char) * this->_content_size);
        int res = fread(this->_content_bin, 1, this->_content_size, this->_document);

		// requete = requete + "HTTP/1.1 200 OK\nContent-Type: image/jpeg\nContent-Length: " + this->_c_size + "\n\n";
		this->_response = this->_response + "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: " + this->_c_size + "\n\n";
        
		char *http = (char *)malloc(sizeof(char) * (this->_response.size() + this->_content_size));
        memcpy(http, this->_response.c_str(), this->_response.size());
        memcpy(http + strlen(http), this->_content_bin, this->_content_size);
        
		
		std::cout 	<< C_RED << "///////////////////////////////////////////////////////////////////////////////////////" << C_RESET << std::endl
					<< C_YELLOW << http << C_RESET << std::endl 
					<< C_RED << "///////////////////////////////////////////////////////////////////////////////////////" << C_RESET << std::endl;
		// printf("http = %s\n", http);
        
		
		write(this->_new_socket , http , this->_response.size() + this->_content_size);
        printf("------------------Hello message sent-------------------/n");
        close(this->_new_socket);
		fclose(this->_document);
		free(http);
		http = NULL;
		free(this->_content_bin);
		this->_content_bin = NULL;
		//////////////////////////////////////////////////////////////////////////////////////
	}

}