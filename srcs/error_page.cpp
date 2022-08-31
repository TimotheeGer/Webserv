#include "color.hpp"
#include "server.hpp"

int server::error_page(int error) {

    std::string error_page{R"(<!DOCTYPE html>
<html>
  <head>
    <style>
      @import url("https://fonts.googleapis.com/css2?family=Didact+Gothic&family=Hind:wght@400;700&display=swap");
      body {
        width: 90%;
        margin: 0 auto;
        background-color: #d2e9f5;
      }

      h1 {
        font-family: "Hind", sans-serif;
      }

      .img {
        width: 100px;
        margin: 0 auto;
        /* border: 1px solid pink; */
      }
      .box {
        margin: 0 auto;
        display: flex;
        flex-direction: column;
        height: 700px;
        justify-content: center;
        justify-items: center;
        /* border: 1px solid green; */
      }

      .text {
        opacity: 0.5;
        line-height: 0%;
        align-self: center;
        /* border: 1px solid blue; */
        text-align: center;
        display: inline-block;
      }
      .line {
        height: 1px;
        background-color: black;
        margin: 1rem;
        opacity: 0.3;
      }
      /* .text_two {
        display: flex;
        text-align: center;
        display: inline-block;
        margin: 0 auto;
        font-size: 7px;
        line-height: 0%;
        font-family: "Didact Gothic", sans-serif;
      } */
    </style>
    <meta charset="utf-8" />
	<title>)"};
    // code error
    std::string error_page_two {R"(</title>
    <link href="https://profile.intra.42.fr/assets/42_logo_black-684989d43d629b3c0ff6fd7e1157ee04db9bb7a73fba8ec4e01543d650a1c607.png" rel="icon" type="image/png">
    <meta name="viewport" content="width=device-width, initial-scale=1" />
  </head>
  <body>
    <div class="box">
      <div class="img">
        <img
          src="https://oms-inventaires.com/wp-content/uploads/2020/09/Inventuren_Icons_Balken.svg"
          alt="logo"
          class="logo"
        />
      </div>
      <div class="text">
        <h1>)"};
    // code error
    std::string error_page_three {R"(</h1>
      </div>
    </div>
  </body>
</html>)"};

    
    std::string final_error_page;

    final_error_page = final_error_page + error_page + get_code_error_convert(error) + error_page_two + get_code_error_convert(error) + error_page_three + '\0';
    
    std::sprintf(this->_code_char, "%d.html", this->code_test);

    std::ofstream ofs;
    ofs.open(this->_code_char, std::ofstream::out);
    if(!ofs.is_open())
      return(EXIT_FAILURE);
    ofs << final_error_page;
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