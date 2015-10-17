//
// Created by Neveralso on 15/3/15.
//

#include "demoniac/io_loop.h"

#include "demoniac/poller/get_poller.h"
#include "demoniac/event_callback.h"
#include "demoniac/log.h"

namespace demoniac {

IOLoop::IOLoop() {
    instance_ = this;
    poller_ = demoniac::poller::GetPoller();
    events_map_.clear();
    quited_ = 0;
}


void IOLoop::addEventCallback(const int& fd, EventCallback e) {

    LOG_DEBUG << "fd" << fd << " Loop event added";

    events_map_.insert(std::make_pair(fd, e));
    poller_->AddEventCallback(fd, e);
}


IOLoop *IOLoop::current() {
    if (instance_) {
        return instance_;
    }
    else {
        instance_ = new IOLoop;
        return instance_;
    }
}


void IOLoop::loop() {
    LOG_INFO << "Loop start.";
    int ready_num;

#if defined(DC_DEBUG)
    int count = 0;
#endif

    while (!quited_) {

#if defined(DC_DEBUG)
        LOG_DEBUG << "Loop " << count++ << " with " << events_map_.size() << " events";
#endif
        ready_num = poller_->Poll(10);

#if defined(DC_DEBUG)
        LOG_DEBUG << ready_num << " events ready";
#endif

        poller_->HandleEvents(events_map_);

    }
}


void IOLoop::quit() {
    quited_ = true;

}


void IOLoop::removeEventCallback(const int &fd) {
#if defined(DC_DEBUG)
    LOG_DEBUG << "fd" << fd << " Loop event removed";
#endif
    events_map_.erase(fd);
}


void IOLoop::start() {
    loop();
}


IOLoop::~IOLoop() {
    delete poller_;
    instance_ = NULL;
}


}