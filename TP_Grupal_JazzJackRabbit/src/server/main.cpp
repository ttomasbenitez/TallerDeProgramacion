#include <iostream>
#include "server.h"

int main(int argc, char* argv[]) {
    try {
        Server server;
        server.start();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Error inesperado!" << std::endl;
    }
}
