#include "../hpp/parse.hpp"

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
			split_in_tabs(this->tab_request[i], c, tab);
			break;
		}
		i++;
	}
	if (tab.size() == 0)
		return "";
	return (tab[x]);
}

std::string Parse::get_method_parse(std::vector<std::string> &request) {

	std::vector<std::string> tab;
	split_in_tabs(this->tab_request[0], " ", tab);
	return (tab[0]);
}

int	Parse::parse_request(std::string request, std::map<std::string, std::string> &map_req) {

	if (split_in_tabs(request, "\n", this->tab_request).size() == 0)
		return(EXIT_FAILURE);
	
	map_req["METHOD"] = get_method_parse(this->tab_request);
	
	// GET
	if (map_req["METHOD"] == "GET")
	{
		map_req["GET"] = "../" + get_request("GET ", " ", 1).erase(0, 1);
		if (map_req["GET"].size() == 3)
			map_req["GET"] = "../html/index.html";
		map_req["Host"] = get_request("Host: ", " ", 1);
		map_req["Accept"] = get_request("Accept: ", " ", 1);	
	}
	if (map_req["METHOD"] == "POST")
	{
		map_req["POST"] = "../" + get_request("POST ", " ", 1).erase(0, 1);
		if (map_req["POST"].size() == 3)
			map_req["POST"] = "../html/index.html";		map_req["user_name"] = get_request("user_name=", "&", 0);
		map_req["user_mail"] = get_request("user_mail=", "&", 1);
		map_req["user_message"] = get_request("user_message=", "&", 2);
		
		std::cout << "MAP_REQ[POST] = " << map_req["POST"] << std::endl;
		std::cout << "MAP_REQ[user name] = " << map_req["user_name"] << std::endl;
		std::cout << "MAP_REQ[user mail] = " << map_req["user_mail"] << std::endl;
		std::cout << "MAP_REQ[user message] = " << map_req["user_message"] << std::endl;
	}

	this->tab_request.clear();
	this->tab_get.clear();
	return (EXIT_SUCCESS);
}
