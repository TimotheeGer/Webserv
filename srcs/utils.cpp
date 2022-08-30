#include "server.hpp"

std::string server::get_code_error_convert(int error) {

	map_code[100] = "100 Continue";
	map_code[101] = "101 Switching Protocols";
	map_code[102] = "102 Processing";
	map_code[103] = "103 Early Hints";
	map_code[200] = "200 OK";
	map_code[201] = "201 Created";
	map_code[202] = "202 Accepted";
	map_code[400] = "400 Bad Request";
	map_code[404] = "404 Not Found";

	if (map_code.count(error))
		return (map_code[error]);
	return (map_code[400]);
}

