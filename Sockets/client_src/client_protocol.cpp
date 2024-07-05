//
// Created by tom on 30/03/24.
//

#include "client_protocol.h"

ClientProtocol::ClientProtocol(const char* hostname, const char* port): socket(hostname, port) {}

std::string ClientProtocol::receive_message() {

    bool was_closed = false;
    uint16_t string_length = 0;
    socket.recvall(&string_length, sizeof(string_length), &was_closed);

    string_length = ntohs(string_length);
    std::vector<char> buffer(string_length);
    socket.recvall(buffer.data(), string_length, &was_closed);

    return std::string(buffer.data(), string_length);
}

std::vector<Action> ClientProtocol::encode_actions_line(std::string& line) {
    std::istringstream actions_line(line);
    std::vector<Action> actions;

    std::string word;
    while (actions_line >> word) {
        if (word == ACTION_JUMP) {
            actions.push_back(JUMP);
        } else if (word == ACTION_RIGHT) {
            actions.push_back(RIGHT);
        } else if (word == ACTION_LEFT) {
            actions.push_back(LEFT);
        } else if (word == ACTION_DUCK) {
            actions.push_back(DUCK);
        } else if (word == ACTION_HIT) {
            actions.push_back(HIT);
        } else {
            std::cerr << UNKNOWN_ACTION_ERR << std::endl;
        }
    }
    actions.push_back(NOP);

    return actions;
}

void ClientProtocol::send_message(std::string line) {

    bool was_closed = false;
    std::vector<Action> actions_line = encode_actions_line(line);
    socket.sendall(actions_line.data(), actions_line.size() * sizeof(Action), &was_closed);
}
