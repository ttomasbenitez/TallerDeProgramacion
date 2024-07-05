#ifndef CLIENT_SEND_HANDLER_H
#define CLIENT_SEND_HANDLER_H

#include "thread.h"
#include "queue.h"
#include "gamestate.h"
#include "socket.h"
#include "liberror.h"
#include <sys/socket.h>

#include <iostream>

class ClientSendHandler: public Thread {
  private:
    Socket& sock;
    std::shared_ptr<Queue<GameState>> s2c_queue;
  public:
    explicit ClientSendHandler(Socket& sock, std::shared_ptr<Queue<GameState>> s2c): sock(sock), s2c_queue(s2c) {}
    void run() override {
      while (this->_keep_running) {
        try {
          GameState state = s2c_queue->pop();
          auto data = state.serialize();
          bool closed = false;
          this->sock.sendall(data.data(), data.size(), &closed);
          if (closed) break;
        } catch (const LibError& e) {
            break;
        } catch (const ClosedQueue& e) {
            break;
        }
      }
      sock.shutdown(SHUT_RDWR);
      sock.close();
      this->_is_alive = false;
    }
};

#endif
