#ifndef __ACTIONS_H__
#define __ACTIONS_H__
#include "thread.h"
#include "queue.h"
#include "clientaction.h"
#include <SDL2pp/SDL2pp.hh>

class Actions: public Thread
{
private:
    Queue<ClientAction>& actionQueue;
public:
    Actions(Queue<ClientAction>& queue);
    void run() override;
    void stop() override;
    void process_actions();
    bool is_Running();
    ~Actions() {}
};


#endif
