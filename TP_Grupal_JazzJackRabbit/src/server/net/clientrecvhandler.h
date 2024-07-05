#ifndef CLIENT_RECV_HANDLER_H
#define CLIENT_RECV_HANDLER_H

#include "thread.h"
#include "queue.h"
#include "clientaction.h"
#include "socket.h"
#include "liberror.h"
#include "gamelogic/gamemanager.h"

#include <iostream>

class ClientRecvHandler: public Thread {
  private:
    Socket& sock;
    int id;
    GameManager& game_manager;
  public:
    explicit ClientRecvHandler(Socket& sock, int id, GameManager& game_manager): sock(sock), id(id), game_manager(game_manager) {}
    void run() override {
      while (this->_keep_running) {
        try {
          uint8_t size;
          bool closed = false;
          this->sock.recvall(&size, sizeof(size), &closed);
          if (closed) break;
          std::string s(size, 0);
          this->sock.recvall(s.data(), size, &closed);
          if (closed) break;
          std::stringstream ss(s);
          auto ca = ClientAction::deserialize(ss);
          ClientMessage cm(id, ca);
          game_manager.route(cm);
        } catch (const LibError& e) {
            ClientMessage cm(id, ClientAction(Action::Quit, 0));
            game_manager.route(cm);
            break;
        } catch (const ClosedQueue& e) {
            break;
        }
      }
      this->_is_alive = false;
    }
};

#endif
