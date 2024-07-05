#include "acceptor.h"
#include "liberror.h"
#include "net/clientiohandler.h"
#include "gamestate.h"
#include "config.h"
#include <optional>
#include <sys/socket.h>
#include <memory>

Acceptor::Acceptor(Socket sock, GameManager& games):
    sock(std::move(sock)),
    games(games)
  {}

void Acceptor::run() {
  while (this->_keep_running) {
    auto peer = this->accept();
    if (!peer) break;
    auto s2c_ptr = std::make_shared<Queue<GameState>>(config.get<int>("limits.sendq"));
    int id = games.add_client(s2c_ptr);
    auto client = std::make_unique<ClientIOHandler>(id, std::move(peer.value()), s2c_ptr, games);
    client->start();
    this->clients.push_back(std::move(client));
    this->reap();
  }
  for (auto& client: this->clients) {
    if (client->is_alive()) client->stop();
    client->join();
  }
  this->_is_alive = false;
}

std::optional<Socket> Acceptor::accept() {
    try {
        return std::optional<Socket>(sock.accept());
    } catch (const LibError& e) {
        return std::nullopt;
    }
}

void Acceptor::stop() {
  Thread::stop();
  this->sock.shutdown(SHUT_RDWR);
  this->sock.close();
}

void Acceptor::reap() {
  for (auto it = this->clients.begin(); it != this->clients.end();) {
    auto& client = *it;
    if (!client->is_alive()) {
      int id = client->get_id();
      client->join();
      this->games.remove_client(id);
      it = this->clients.erase(it);
    } else {
      it++;
    }
  }
  games.reap();
}
