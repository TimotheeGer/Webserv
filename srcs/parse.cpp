#include "parse.hpp"
#include "color.hpp"

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


std::string Parse::get_request(std::string word) {
	
	int i = 0;

	std::vector<std::string> tab;
	while (i < this->tab_request.size())
	{
		if (this->tab_request[i].find(word) != -1)
		{
			split_in_tabs(this->tab_request[i], " ", tab);
			break;
		}
		i++;
	}
	return (tab[1]);
}

int	Parse::parse_request(std::string request, std::map<std::string, std::string> &map_req) {

	if (split_in_tabs(request, "\n", this->tab_request).size() == 0)
		return(EXIT_FAILURE);
	map_req["GET"] = get_request("GET ").erase(0, 1);
	map_req["Host"] = get_request("Host: ");
	map_req["Accept"] = get_request("Accept: ");


	this->tab_request.clear();
	this->tab_get.clear();
	return (EXIT_SUCCESS);
}
