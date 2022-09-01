#include "../hpp/server.hpp"

void	server::init_map_code(void) {

	map_code[100] = "100 Continue";
	map_code[101] = "101 Switching Protocols";
	map_code[102] = "102 Processing";
	map_code[103] = "103 Early Hints";
	map_code[200] = "200 OK";
	map_code[201] = "201 Created";
	map_code[202] = "202 Accepted";
	map_code[400] = "400 Bad Request";
	map_code[404] = "404 Not Found";
	map_code[501] = "501 Not Implemented";
}

std::string server::get_code_error_convert(int error) {

	if (map_code.count(error))
		return (map_code[error]);
	return (map_code[400]);
}

int server::is_error_code(int error) {

	if (map_code.count(error))
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

