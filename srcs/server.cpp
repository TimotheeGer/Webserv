#include "color.hpp"
#include "server.hpp"

// ************************************************************************** //
//                               Constructor                             	  //
// ************************************************************************** //

server::server(void) { 
		
	std::cout << C_GREEN << "\n- Launch Server -\n" << C_RESET << std::endl;
	
	this->_addrlen = sizeof(this->_address);
	this->_port = 8080;
	// this->_error_code = "501";
	this->_address.sin_family = AF_INET;
    this->_address.sin_addr.s_addr = INADDR_ANY;
    this->_address.sin_port = htons( this->_port );
	this->_content_bin = NULL;
	this->_content_bin_two = NULL;
	this->http = NULL;
    
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

int server::get_request(void) {
    
	if (!read( this->_new_socket , this->_request, 30000))
		return(EXIT_FAILURE);
	
	this->request_string = this->_request;
	std::cout 	<< C_RED << "--------------------Requete recu--------------------" << C_RESET << std::endl;
	std::cout << C_BOLDGREEN << this->_request << C_RESET << std::endl;
	std::cout 	<< C_RED << "--------------------Requete recu--------------------" << C_RESET << std::endl << std::endl;
	return(EXIT_SUCCESS);
}

int server::open_basics_files(void) {

	this->parse_r.parse_request(this->_request, this->map_serv);
	if (this->map_serv["GET"] == "favicon.ico")
	{
		std::cout << "Favicon fail" << std::endl;
		return (EXIT_FAILURE);
	}
	std::cout << C_BLUE << "map_serv = [" << this->map_serv["GET"] <<  "]\n" << C_RESET << std::endl;
	
	std::ifstream input(this->map_serv["GET"], std::ios::binary);
	if (!input.is_open())
		return (404);
	input.seekg(0, std::ios::end);
	this->_content_size = input.tellg();
	input.seekg(0, std::ios::beg);
	std::sprintf(this->_c_size, "%lu", this->_content_size);

	if (!(this->_content_bin = (char*)malloc(sizeof(char) * this->_content_size)))
		return (EXIT_FAILURE);
	input.read(this->_content_bin, this->_content_size);

	std::cout 	<< C_BOLDCYAN << "--------------------Bin Make--------------------" << C_RESET << std::endl;
	std::cout << C_YELLOW << this->_content_bin << C_RESET << std::endl;
	std::cout 	<< C_BOLDCYAN << "--------------------Bin Make--------------------" << C_RESET << std::endl << std::endl;

	return (EXIT_SUCCESS);
}


std::string server::write_response(void) {

	std::string http;
	std::string code;
	std::string content_type;
	std::string content_length;

	http = "HTTP/1.1 ";
	code = code + get_code_error_convert(this->code_test) + "\n";
	content_type = content_type + "Content-Type: "
								+ this->mimes_r.getTypes(this->map_serv["GET"].substr(this->map_serv["GET"].find('.', 0), std::string::npos)) + "\n";
	content_length = content_length + "Content-Length: " + this->_c_size + "\n\n";

	return http + code + content_type + content_length;
}


int server::make_response(void) {

	this->_response = write_response();

	if (this->code_test != 404) {

		if (!(this->http = (char *)malloc(sizeof(char) * (this->_response.size() + this->_content_size + 1))))
			return (EXIT_FAILURE);
		memset(this->http, 0, this->_response.size() + this->_content_size + 1);
		memcpy(this->http, this->_response.c_str(), this->_response.size());
    	memcpy(this->http + strlen(http), this->_content_bin, this->_content_size);

		std::cout 	<< C_RED << "--------------------Response + Bin--------------------" << C_RESET << std::endl
					<< C_GREEN << this->http << C_RESET << std::endl 
					<< C_RED << "--------------------Response + Bin--------------------" << C_RESET << std::endl << std::endl;
	}
	if (this->code_test == 404) {
		
		if (!(this->http = (char *)malloc(sizeof(char) * (this->_response.size() + error_page().size() + 1))))
			return (EXIT_FAILURE);
		memset(this->http, 0, this->_response.size() + this->_content_size + 1);
		memcpy(this->http, this->_response.c_str(), this->_response.size());
    	memcpy(this->http + strlen(http), this->_content_bin, this->_content_size);
	}

	return (EXIT_SUCCESS);
}


int server::send_message(void) {

	if (write(this->_new_socket , this->http , this->_response.size() + this->_content_size) == -1)
		return(EXIT_FAILURE);
	std::cout 	<< C_BOLDGREEN << "--------------------Response Send--------------------" << C_RESET << std::endl;
	memset(this->http, 0, this->_response.size() + this->_content_size);
	return(EXIT_SUCCESS);
}


void server::clear_server(void) {

	if (this->http != NULL)
	{
		free(this->http);
		this->http = NULL;
	}
	if (this->_content_bin != NULL)
	{
		free(this->_content_bin);
		this->_content_bin = NULL;
	}
	this->map_serv.clear();
	this->_response.clear();    
	close(this->_new_socket);
}



int server::wait_connection(void) {

	while(1)
	{
		std::cout << C_BLUE << "\n- Waiting for new connection -\n" << C_RESET << std::endl;
		if (new_socket())
			return(EXIT_FAILURE);
		if (get_request())
			return(EXIT_FAILURE);
		if ((this->code_test = open_basics_files()) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (make_response())
			return (EXIT_FAILURE);	
		if (send_message())
			return(EXIT_FAILURE);
		clear_server();
	}
	return (EXIT_SUCCESS);
}