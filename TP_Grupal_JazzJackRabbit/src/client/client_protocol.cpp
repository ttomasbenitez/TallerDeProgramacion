#include "client_protocol.h"
#include "gamestate.h"
#include <arpa/inet.h>
#include <iostream>
#define SIZE_OF_ACTION 1
#define SIZE_OF_DATA 3


Protocol::Protocol(const std::string& hostname, const std::string& servname):skt(hostname.c_str(), servname.c_str()){
    was_close = false;
}

void Protocol::send(ClientAction action){
    std::vector<char> data = action.serialize();
    this->skt.sendall(data.data(), data.size(), &was_close);
}

GameState Protocol::recive(){
    uint16_t total_size;
    skt.recvall(&total_size, sizeof(total_size), &was_close);
    if (was_close)
    {
        GameState state;
        was_close = true;
        return state;
    }
    total_size = be16toh(total_size);
    std::string s(total_size, 0);
    skt.recvall(s.data(), total_size,&was_close);
    std::stringstream info(s);
    GameState state = GameState::deserialize(info);
    return state;
}

bool Protocol::is_close(){
    return was_close;
}

void Protocol::close(){
    skt.shutdown(2);
    skt.close();
}