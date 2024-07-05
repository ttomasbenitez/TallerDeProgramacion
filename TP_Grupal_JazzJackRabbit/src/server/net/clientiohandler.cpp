#include "clientiohandler.h"
#include "clientsendhandler.h"
#include "clientrecvhandler.h"
#include <sys/socket.h>

ClientIOHandler::ClientIOHandler(int id, Socket sock, std::shared_ptr<Queue<GameState>> s2c, GameManager& game_manager):
  id(id),
  sock(std::move(sock)),
  s2c_queue(s2c),
  game_manager(game_manager),
  send(this->sock, s2c),
  recv(this->sock, id, game_manager)
{}

void ClientIOHandler::start() {
  send.start();
  recv.start();
}

void ClientIOHandler::stop() {
  send.stop();
  recv.stop();
  if (send.is_alive() && recv.is_alive()) {
    try {
      sock.shutdown(SHUT_RDWR);
    } catch (const LibError& e) {
      // already disconnected
    }
    sock.close();
  }
}

void ClientIOHandler::join() {
  send.join();
  recv.join();
}

bool ClientIOHandler::is_alive() const {
  return send.is_alive() || recv.is_alive();
}

int ClientIOHandler::get_id() {
  return this->id;
}
