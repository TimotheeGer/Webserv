#include "color.hpp"
#include "server.hpp"

std::string server::error_page() {

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
     
    std::string error_page_two {R"( Not Found</title>
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
    
    std::string error_page_three {R"( Not Found</h1>
      </div>
    </div>
  </body>
</html>)"};

    std::string final_error_page = error_page + this->_error_code + error_page_two + this->_error_code + error_page_three;
    return(final_error_page);
}