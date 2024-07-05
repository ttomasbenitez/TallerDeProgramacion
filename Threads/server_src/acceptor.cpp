#include "acceptor.h"

Acceptor::Acceptor(Socket& acceptor_skt): socket(std::move(acceptor_skt)) {}

void Acceptor::run() {
    Game current_game(monitor, game_commands);
    current_game.start();

    do {
        try {
            Socket client_socket = socket.accept();
            connect_client(client_socket);
        }

        catch (const std::exception& e) {
            syslog(LOG_CRIT, "Error: %s", e.what());
            closelog();
        }

    } while (_keep_running);

    kill_all();
    current_game.stop();
    current_game.join();
}

void Acceptor::reap_dead() {
    senders.remove_if([](Sender* sender) {
        if (!sender->is_alive()) {
            sender->join();
            delete sender;
            return true;
        }
        return false;
    });
}

void Acceptor::stop() {
    _keep_running = false;
    _is_alive = false;
    socket.shutdown(SHUT_RDWR);
    socket.close();
}

void Acceptor::kill_all() {
    for (auto& sender: senders) {
        sender->stop();
        sender->join();
        delete sender;
    }
    senders.clear();
}

void Acceptor::connect_client(Socket& client_socket) {
    Sender* sender = new Sender(client_socket, monitor, game_commands);
    sender->start();
    reap_dead();
    senders.push_back(sender);
}
