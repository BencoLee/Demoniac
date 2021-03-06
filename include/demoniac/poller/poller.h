//
// Created by Neveralso on 15/3/17.
//

#ifndef _DEMONIAC_POLLER_POLLER_H_
#define _DEMONIAC_POLLER_POLLER_H_

#include <vector>
#include <map>

namespace demoniac {

class EventCallback;

namespace poller {

const int MAX_READY_EVENTS_NUM = 500;

class Poller{
public:

    Poller();

    virtual ~Poller() = 0;

    virtual int Poll(int time_out) = 0;

    virtual void HandleEvents(const std::map<int, EventCallback>& events_map) = 0;

    virtual void AddEventCallback(const int& fd, const EventCallback& e) = 0;

    virtual void UpdateEventCallback(const int& fd, const EventCallback& e) = 0;

    virtual void DeleteEventCallback(const int& fd) = 0;

private:

    Poller& operator = (const Poller& poller) = delete;
    Poller(const Poller& poller) = delete;
};


}
}


#endif //_DEMONIAC_POLLER_H_
