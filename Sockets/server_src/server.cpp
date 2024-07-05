//
// Created by tom on 28/03/24.
//

#include "server_implementation.h"

#define SUCCESS 0
#define ERROR 1
#define PORT argv[1]

int main(int argc, char* argv[]) {

    if (argc != 2) {
        std::cerr << "Expected one argument." << std::endl;
        return ERROR;
    }

    Server server(PORT);
    server.run();

    return SUCCESS;
}
