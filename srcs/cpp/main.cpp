#include "../hpp/server.hpp"

int main() {

    server 	tim;

    tim.init_socket();
    tim.wait_connection();
    
    return 0;
}