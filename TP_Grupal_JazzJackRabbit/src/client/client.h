#ifndef CLIENT_H
#define CLIENT_H

#include <vector>
#include <thread.h>
#include <mutex>
#include <condition_variable>

class Client
{
private:
    std::mutex exit_lock;
    std::condition_variable exit_cv;
public:
    Client();
    void start(const char* hostname, const char* servname);
    void notify_exit();
    ~Client() {}
};


#endif