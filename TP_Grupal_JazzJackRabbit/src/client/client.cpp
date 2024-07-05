#include <client.h>
#include <unistd.h>
#include <vector>
#include "thread.h"
#include "graphics.h"
#include "actions.h"
#include "sender_client.h"
#include "reciver_client.h"
#include "queue.h"
#include "client_protocol.h"
#include "clientaction.h"
#include "gamestate.h"


Client::Client()
{
}

void Client::start(const char *hostname, const char *servname)
{
    std::vector<Thread *> threads;
    Queue<ClientAction> queueActions;
    Queue<GameState> responseQueue; 
    Protocol protocol(hostname, servname);

    Thread* sender = new Sender(queueActions, protocol, *this);
    Thread* reciver = new Reciver(responseQueue, protocol, *this);
    Thread *graphics = new Graphics(responseQueue, queueActions, *this);

    threads.push_back(sender);
    threads.push_back(reciver);
    threads.push_back(graphics);

    for (Thread *thread : threads)
    {
        thread->start();
    }
    {
        std::unique_lock<std::mutex> lk(exit_lock);
        exit_cv.wait(lk, [&]{ return !(graphics->is_alive())||!(sender->is_alive())||!reciver->is_alive(); });
    }
    for (Thread *thread : threads)
    {
        thread->stop();
        thread->join();
        delete thread;
    }
}

void Client::notify_exit() {
    std::unique_lock<std::mutex> lk(exit_lock);
    exit_cv.notify_all();
}
