//
// Created by tom on 28/03/24.
//

#include "server_implementation.h"

#define SUCCESS 0
#define ARGS_ERROR 1
#define PORT argv[1]
#define EXPECTED_ARGC 2


int main(int argc, char* argv[]) {

    if (argc != EXPECTED_ARGC) {
        std::cerr << "Expected one argument." << std::endl;
        return ARGS_ERROR;
    }

    Server server(PORT);
    server.run();

    return SUCCESS;
}
