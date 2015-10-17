//
// Created by Neveralso on 15/3/15.
//

#ifndef _DEMONIAC_IOLOOP_H_
#define _DEMONIAC_IOLOOP_H_

#include <iostream>
#include <vector>
#include <map>

namespace demoniac {


class EventCallback;

namespace poller{

    class Poller;

    class KqueuePoller;

    class EpollPoller;

}


class IOLoop {
public:

    static IOLoop* current();

    void loop();

    void quit();

    void addEventCallback(const int& fd, EventCallback e);

    void removeEventCallback(const int &fd);

    void start();

    ~IOLoop();

private:

    static IOLoop *instance_;
    bool quited_;
    demoniac::poller::Poller *poller_;
    std::map<int, EventCallback> events_map_;

    IOLoop();

    IOLoop(const IOLoop& ioloop) = delete;
    IOLoop& operator = (const IOLoop& ioloop) = delete;
};

}


#endif //_DEMONIAC_IOLOOP_H_
