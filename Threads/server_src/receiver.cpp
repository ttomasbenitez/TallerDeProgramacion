#include "receiver.h"

Receiver::Receiver(ServerProtocol& server_protocol, Queue<enum Command>& commands):
        protocol(server_protocol), game_commands(commands) {}

void Receiver::receive_message() {
    Command command = protocol.receive_command();
    game_commands.push(command);
}

void Receiver::stop() {
    _is_alive = false;
    _keep_running = false;
}

void Receiver::run() {
    while (!protocol.skt_was_closed()) {
        receive_message();
    }
}
