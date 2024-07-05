//
// Created by tom on 28/03/24.
//

#include <iostream>

#include "client_implementation.h"

#define SUCCESS 0
#define ERROR 1
#define HOSTNAME argv[1]
#define PORT argv[2]


int main(int argc, char* argv[]) {

    if (argc != 3) {
        std::cerr << "Expected two arguments." << std::endl;
        return ERROR;
    }

    Client client(HOSTNAME, PORT);
    client.run();

    return SUCCESS;
}
