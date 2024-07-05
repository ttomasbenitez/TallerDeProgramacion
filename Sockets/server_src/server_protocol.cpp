//
// Created by tom on 31/03/24.
//
#include "server_protocol.h"

ServerProtocol::ServerProtocol(Socket& client_socket): socket(std::move(client_socket)) {}

std::vector<std::string> ServerProtocol::decode_received_line(uint8_t* data, int received_number) {

    std::vector<std::string> received_actions;
    for (int i = 0; i < received_number; i++) {
        switch (data[i]) {
            case NOP:
                break;
            case JUMP:
                received_actions.push_back(ACTION_JUMP);
                break;
            case RIGHT:
                received_actions.push_back(ACTION_RIGHT);
                break;
            case LEFT:
                received_actions.push_back(ACTION_LEFT);
                break;
            case DUCK:
                received_actions.push_back(ACTION_DUCK);
                break;
            case HIT:
                received_actions.push_back(ACTION_HIT);
                break;
            default:
                std::cerr << UNKNOWN_ACTION_ERR << std::endl;
                break;
        }
    }

    return received_actions;
}

void ServerProtocol::send_received_line(const std::string& line, bool* was_closed) {
    int length = line.length();
    uint16_t chars_to_send = htons(length);

    socket.sendall(&chars_to_send, sizeof(chars_to_send), was_closed);
    socket.sendall(line.data(), length, was_closed);
}


std::vector<uint8_t> ServerProtocol::receive_line(bool* was_closed) {

    std::vector<uint8_t> buffer;
    do {
        uint8_t received_byte;
        socket.recvall(&received_byte, sizeof(received_byte), was_closed);

        if (*was_closed) {
            return {};
        }

        buffer.push_back(received_byte);

    } while (buffer.back() != NOP);

    return buffer;
}
