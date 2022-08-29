#include "server.hpp"

int main() {

    server 	tim;
	// Parse 	theo;

    tim.init_socket();
    tim.wait_connection();

	// theo.parse_request(req);
}

// 	std::string req {R"(GET /favicon.ico HTTP/1.1
// Host: localhost:8080
// Connection: keep-alive
// User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/104.0.5112.81 Safari/537.36
// Accept: image/avif,image/webp,image/apng,image/svg+xml,image/*,*/*;q=0.8
// Sec-GPC: 1
// Sec-Fetch-Site: same-origin
// Sec-Fetch-Mode: no-cors
// Sec-Fetch-Dest: image
// Referer: http://localhost:8080/
// Accept-Encoding: gzip, deflate, br
// Accept-Language: en-US,en;q=0.9

// st: document
// Accept-Encoding: gzip, deflate, br)"};