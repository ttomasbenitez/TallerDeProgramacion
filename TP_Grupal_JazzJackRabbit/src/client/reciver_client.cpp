#include "reciver_client.h"
#include "liberror.h"
#include "client.h"

Reciver::Reciver(Queue<GameState>& queue, Protocol& protocol, Client& client): responseQueue(queue), protocol(protocol), client(client) {}

void Reciver::run(){
    while ( _keep_running && !protocol.is_close())
    {
      try
      {
      GameState gameState = protocol.recive();
      if (protocol.is_close())
      {
        _keep_running = false;
        break;
      }
      responseQueue.try_push(gameState);
      }
      catch(const LibError& e)
      {
        _keep_running = false;
      }
      catch(const ClosedQueue& e){
        _keep_running = false;
      }
    }
    client.notify_exit();
}

void Reciver::stop(){
  _keep_running = false;
  try
  {
    responseQueue.close();
  }
  catch(const ClosedQueue& e)
  {
  }
  

}