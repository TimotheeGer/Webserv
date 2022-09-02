#include "../hpp/server.hpp"


int server::is_favicon(void) {

	std::cout << C_MAGENTA << "[TEST POST5]" << C_RESET << std::endl;
   	if (this->_map_request[get_method()] == "../favicon.ico")
	{
		std::cout << "Favicon fail" << std::endl;
		return (EXIT_SKIP);
	}
    else
        return (EXIT_SUCCESS); 
}

int server::open_basics_files(void) {

	this->parse_r.parse_request(this->_request, this->_map_request);

	if (is_favicon() == EXIT_SKIP)
		return (EXIT_SKIP);

	std::cout << C_BLUE << "_map_request GET  = [" << this->_map_request["GET"].c_str() <<  "]\n" << C_RESET << std::endl;
	std::cout << C_BLUE << "_map_request POST = [" << this->_map_request["POST"].c_str() <<  "]\n" << C_RESET << std::endl;
	
	std::ifstream input(this->_map_request[get_method()], std::ios::binary);
	if (!input.is_open())
	{
		std::cout << C_MAGENTA << "PATH = " << this->_map_request[get_method()].c_str() << C_RESET << std::endl;
		return (make_bin_error_page(404));
	}

	input.seekg(0, std::ios::end);
	this->_content_size = input.tellg();
	input.seekg(0, std::ios::beg);
	std::sprintf(this->_c_size, "%lu", this->_content_size);

	if (!(this->_content_bin = (char*)malloc(sizeof(char) * this->_content_size))) {

		std::cout << C_BLUE << "[TEST2]\n" << C_RESET << std::endl;
		return (EXIT_FAILURE);
	}
	input.read(this->_content_bin, this->_content_size);

	std::cout 	<< C_BOLDCYAN << "--------------------Bin Make--------------------" << C_RESET << std::endl;
	std::cout << C_YELLOW << this->_content_bin << C_RESET << std::endl;
	std::cout 	<< C_BOLDCYAN << "--------------------Bin Make--------------------" << C_RESET << std::endl << std::endl;

	return (200);
}