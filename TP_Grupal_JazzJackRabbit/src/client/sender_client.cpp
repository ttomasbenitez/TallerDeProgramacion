#include "sender_client.h"
#include "client_protocol.h"
#include "socket.h"
#include "liberror.h"
#include "client.h"

Sender::Sender(Queue<ClientAction>& queue, Protocol& protocol, Client& client): actionQueue(queue), protocol(protocol), client(client){
}

void Sender::run(){
    
    while (_keep_running && !protocol.is_close())
    {
        try
        {
            ClientAction action;
            action = actionQueue.pop();
            protocol.send(action);
        }
        catch(const ClosedQueue& e)
        {
            _keep_running = false;
            break;
        }catch(const LibError& e){
            _keep_running = false;
            break;
        }
        
        
    }
    client.notify_exit();

}

bool Sender::is_running(){
    return _keep_running;
}

void Sender::stop(){
    _keep_running = false;
    try
    {
       actionQueue.close();
    }
    catch(const std::exception& e)
    {  
    }    
    protocol.close();
}