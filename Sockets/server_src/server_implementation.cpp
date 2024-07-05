//
// Created by tom on 10/04/24.
//

#include "server_implementation.h"

Server::Server(const char* port): socket(port) {}

void Server::run() {
    Socket client_socket = socket.accept();
    GameLogic current_game;
    ServerProtocol protocol(client_socket);


    bool was_closed = false;
    while (!was_closed) {

        std::vector<uint8_t> buffer = protocol.receive_line(&was_closed);
        if (buffer.empty()) {
            break;
        }

        std::vector<std::string> decoded_line =
                protocol.decode_received_line(buffer.data(), buffer.size());
        std::string game_actions =
                current_game.filter_combos(decoded_line.data(), decoded_line.size());
        protocol.send_received_line(game_actions, &was_closed);
    }

    std::cout << "Actions: " << current_game.get_performed_actions() << std::endl;
}
