//
// Created by tom on 31/03/24.
//
#include "server_protocol.h"

ServerProtocol::ServerProtocol(Socket& client_socket):
        socket(std::move(client_socket)), was_closed(false) {}

bool ServerProtocol::skt_was_closed() { return was_closed.load(); }

Command ServerProtocol::decode_received_command(const uint8_t& received_command) {

    if (received_command != ATTACK) {
        std::cerr << UNKNOWN_COMMAND_ERR << std::endl;
        return ERROR;
    }
    return ATACAR_CMD;
}

void ServerProtocol::send_message(GameInfo& message_info) {
    uint16_t alive_enemies = htons(message_info.get_alive_enemies());
    uint16_t dead_enemies = htons(message_info.get_dead_enemies());
    uint8_t event = message_info.get_event_type();
    uint8_t start = MESS_START;

    bool closed = false;

    socket.sendall(&start, sizeof(start), &closed);
    socket.sendall(&alive_enemies, sizeof(alive_enemies), &closed);
    socket.sendall(&dead_enemies, sizeof(dead_enemies), &closed);
    socket.sendall(&event, sizeof(event), &closed);

    was_closed.store(closed);
}


Command ServerProtocol::receive_command() {

    bool closed = skt_was_closed();

    uint8_t received_byte;
    socket.recvall(&received_byte, sizeof(received_byte), &closed);
    was_closed.store(closed);

    if (closed) {
        return ERROR;
    }

    return decode_received_command(received_byte);
}
