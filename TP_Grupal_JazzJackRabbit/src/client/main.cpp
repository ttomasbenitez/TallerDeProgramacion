#include <iostream>
#include <ios>

#include <SDL2pp/SDL2pp.hh>

#include "client.h"
#include "graphics.h"

using namespace SDL2pp;

int main(int argc, char *argv[])
{
    
    const char *hostname = "localhost";
    const char *servname = "1234";
    Client client;
    client.start(hostname, servname);
}
