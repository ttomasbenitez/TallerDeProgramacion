//
// Created by tom on 28/03/24.
//

#include <iostream>

#include "client_implementation.h"

#define SUCCESS 0
#define ARGS_ERROR 1
#define HOSTNAME argv[1]
#define PORT argv[2]
#define EXPECTED_ARGC 3


int main(int argc, char* argv[]) {

    if (argc != EXPECTED_ARGC) {
        std::cerr << "Expected two arguments." << std::endl;
        return ARGS_ERROR;
    }

    Client client(HOSTNAME, PORT);
    client.run();

    return SUCCESS;
}
