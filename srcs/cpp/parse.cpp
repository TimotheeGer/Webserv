#include "../hpp/parse.hpp"
#include "../hpp/color.hpp"

Parse::Parse() {}

Parse::~Parse() {}

std::vector<std::string> Parse::split_in_tabs(std::string request, std::string del, std::vector<std::string> &tab) {

	size_t pos = 0;

	if (!request.length())
		return (tab);	
	while ((pos = request.find(del)) != std::string::npos) {

		tab.push_back(request.substr(0, pos));
		request.erase(0, pos + del.length());
	}
	tab.push_back(request);
	return (tab);
}


std::string Parse::get_request(std::string word, std::string c, int x) {
	
	int i = 0;

	std::vector<std::string> tab;
	while (i < this->tab_request.size())
	{
		if (this->tab_request[i].find(word) != -1)
		{
		std::cout << "tab_request = " << tab_request[i] << std::endl;
			split_in_tabs(this->tab_request[i], c, tab);
			break;
		}
		i++;
	}
	if (tab.size() == 0)
		return "";
	return (tab[x]);
}

int	Parse::parse_request(std::string request, std::map<std::string, std::string> &map_req) {

	if (split_in_tabs(request, "\n", this->tab_request).size() == 0)
		return(EXIT_FAILURE);
	
	
	// GET
	map_req["GET"] = "../" + get_request("GET ", " ", 1).erase(0, 1);
	if (map_req["GET"].size() == 3)
		map_req["GET"] = "../html/index.html";
	map_req["Host"] = get_request("Host: ", " ", 1);
	map_req["Accept"] = get_request("Accept: ", " ", 1);

	std::cout << C_MAGENTA << "[TEST POST1]" << C_RESET << std::endl;
	// POST
	map_req["POST"] = get_request("POST ", " ", 1);
	map_req["user_name"] = get_request("user_name=", "&", 0);
	map_req["user_mail"] = get_request("user_mail=", "&", 1);
	map_req["user_message"] = get_request("user_message=", "&", 2);

	std::cout << C_MAGENTA << "[TEST POST2]" << C_RESET << std::endl;
	if (map_req["POST"].size() > 0) {
	std::cout << C_MAGENTA << "[TEST POST3]" << C_RESET << std::endl;
	std::cout << "MAP_REQ[POST] = " << map_req["POST"] << std::endl;
	std::cout << "MAP_REQ[user name] = " << map_req["user_name"] << std::endl;
	std::cout << "MAP_REQ[user mail] = " << map_req["user_mail"] << std::endl;
	std::cout << "MAP_REQ[user message] = " << map_req["user_message"] << std::endl;
	}

	std::cout << C_MAGENTA << "[TEST POST4]" << C_RESET << std::endl;
	this->tab_request.clear();
	this->tab_get.clear();
	return (EXIT_SUCCESS);
}
