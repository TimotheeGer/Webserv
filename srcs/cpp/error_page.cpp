#include "../hpp/server.hpp"

int server::error_page(int error) {

    _error_page_html += "<!DOCTYPE html>\n\
<html>\n\
	<head>\n\
		<style>\n\
			@import url(\"https://fonts.googleapis.com/css2?family=Didact+Gothic&family=Hind:wght@400;700&display=swap\");\n\
			body {\n\
  				width: 90%;\n\
  				margin: 0 auto;\n\
  				background-color: #d2e9f5;\n\
			}\n\
			h1 {\n\
			  font-family: \"Hind\", sans-serif;\n\
			}\n\
			.img {\n\
			  width: 100px;\n\
			  margin: 0 auto;\n\
			  /* border: 1px solid pink; */\n\
			}\n\
			.box {\n\
			  margin: 0 auto;\n\
			  display: flex;\n\
			  flex-direction: column;\n\
			  height: 700px;\n\
			  justify-content: center;\n\
			  justify-items: center;\n\
			  /* border: 1px solid green; */\n\
			}\n\
			.text {\n\
			  opacity: 0.5;\n\
			  line-height: 0%;\n\
			  align-self: center;\n\
			  /* border: 1px solid blue; */\n\
			  text-align: center;\n\
			  display: inline-block;\n\
			}\n\
			.line {\n\
			  height: 1px;\n\
			  background-color: black;\n\
			  margin: 1rem;\n\
			  opacity: 0.3;\n\
			}\n\
			/* .text_two {\n\
			  display: flex;\n\
			  text-align: center;\n\
			  display: inline-block;\n\
			  margin: 0 auto;\n\
			  font-size: 7px;\n\
			  line-height: 0%;\n\
			  font-family: \"Didact Gothic\", sans-serif;\n\
			} */\n\
		</style>\n\
		<meta charset=\"utf-8\" />\n\
	<title>";
	
	_error_page_html += get_code_error_convert(error);
    
	_error_page_html += "(</title>\n\
	<link href=\"https://profile.intra.42.fr/assets/42_logo_black-684989d43d629b3c0ff6fd7e1157ee04db9bb7a73fba8ec4e01543d650a1c607.png\" rel=\"icon\" type=\"image/png\">\n\
	<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\" />\n\
	</head>\n\
	<body>\n\
		<div class=\"box\">\n\
		<div class=\"img\">\n\
			<img\n\
			src=\"https://oms-inventaires.com/wp-content/uploads/2020/09/Inventuren_Icons_Balken.svg\"\n\
			alt=\"logo\"\n\
			class=\"logo\"\n\
			/>\n\
		</div>\n\
		<div class=\"text\">\n\
			<h1>";
	_error_page_html += get_code_error_convert(error);
	
	_error_page_html += "</h1>\n\
			</div>\n\
		</div>\n\
	</body>\n\
</html>";
    
    std::sprintf(this->_code_char, "%d.html", this->code_test);

    std::ofstream ofs;
    ofs.open(this->_code_char, std::ofstream::out);
    if(!ofs.is_open())
      return(EXIT_FAILURE);
    ofs << _error_page_html;
    ofs.close();
    
    return(EXIT_SUCCESS);
}

int	server::make_bin_error_page(int error) {

	if (error_page(error) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	
	std::ifstream input(this->_code_char, std::ios::binary);
	if (!input.is_open())
		return (EXIT_FAILURE);
	
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
	
	return (error);
}