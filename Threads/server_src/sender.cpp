#include "sender.h"

Sender::Sender(Socket& client_socket, ClientsQueuesMonitor& clients_monitor,
               Queue<enum Command>& commands):
        protocol(client_socket),
        monitor(clients_monitor),
        game_commands(commands),
        messages_to_send(MAX_SIZE) {}

void Sender::send_message(GameInfo& message) { protocol.send_message(message); }

void Sender::stop() {
    _is_alive = false;
    _keep_running = false;
    messages_to_send.close();
}

void Sender::run() {

    int index = monitor.add_client_queue(messages_to_send);

    Receiver receiver(protocol, game_commands);
    receiver.start();


    while (!protocol.skt_was_closed()) {

        try {
            GameInfo message = messages_to_send.pop();
            send_message(message);
        } catch (const std::exception& e) {
            syslog(LOG_CRIT, "Error: %s", e.what());
            closelog();
            break;
        }
    }

    monitor.remove_client_queue(index);
    receiver.stop();
    receiver.join();
}
