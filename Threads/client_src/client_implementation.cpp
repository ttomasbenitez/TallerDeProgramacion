//
// Created by tom on 10/04/24.
//

#include "client_implementation.h"

Client::Client(const char* hostname, const char* port):
        protocol(hostname, port), finish_communication(false) {}


void Client::receive_message(const std::string& message_count) {

    int lines_to_read = std::stoi(message_count);
    for (int i = 0; i < lines_to_read; i++) {

        GameInfo response = protocol.receive_message();
        response.print_info();
    }
}


void Client::process_action(std::string& line) {

    std::istringstream actions_line(line);
    std::string word;
    while (actions_line >> word) {
        if (word == STR_ATACAR) {
            protocol.send_attack_message();

        } else if (word == STR_LEER) {
            actions_line >> word;
            receive_message(word);

        } else if (word == STR_SALIR) {
            finish_communication = true;

        } else {
            std::cerr << UNKNOWN_COMMAND_ERR << std::endl;
        }
    }
}


void Client::run() {

    std::string line;
    while (std::getline(std::cin, line)) {
        process_action(line);
        if (finish_communication) {
            break;
        }
    }
}
