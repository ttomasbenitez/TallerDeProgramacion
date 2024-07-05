//
// Created by tom on 30/03/24.
//

#include "client_protocol.h"

ClientProtocol::ClientProtocol(const char* hostname, const char* port): socket(hostname, port) {}

GameInfo ClientProtocol::receive_message() {

    bool was_closed = false;

    uint8_t start;
    socket.recvall(&start, sizeof(start), &was_closed);

    uint16_t alive_enemies;
    socket.recvall(&alive_enemies, sizeof(alive_enemies), &was_closed);

    uint16_t dead_enemies;
    socket.recvall(&dead_enemies, sizeof(dead_enemies), &was_closed);

    uint8_t event;
    socket.recvall(&event, sizeof(event), &was_closed);

    dead_enemies = ntohs(dead_enemies);
    alive_enemies = ntohs(alive_enemies);


    return GameInfo(alive_enemies, dead_enemies, event);
}

void ClientProtocol::send_attack_message() {

    bool was_closed = false;
    uint8_t attack = ATTACK;
    socket.sendall(&attack, sizeof(attack), &was_closed);
}
