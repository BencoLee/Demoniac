//
// Created by Neveralso on 15/3/19.
//

#include "demoniac/tcp/tcp_connection.h"

#include <sys/socket.h>

#include "demoniac/io_loop.h"
#include "demoniac/tcp/tcp_handler.h"
#include "demoniac/tcp/tcp_server.h"
#include "demoniac/event_callback.h"

namespace demoniac {
namespace tcp {


TCPConnection::TCPConnection(const int &fd,
                             const std::string &from_address,
                             const std::function<void *()> &handler_generator,
                             TCPServer *tcp_server) {
    fd_ = fd;
    from_address_ = from_address;
    tcp_server_ = tcp_server;
    handler_ = (TCPHandler * )(handler_generator());
    handler_->init(this, from_address);

    demoniac::EventCallback e;
    e.SetReadCallback([this](const int& fd, const int& data){
        this->ReadCallback(fd, data);
    });
    e.SetWriteCallback([this](const int& fd, const int& data){
        this->WriteCallback(fd, data);
    });
    e.SetCloseCallback([this](const int& fd, const int& data){
        this->CloseCallback(fd, data);
    });
    demoniac::IOLoop::current()->addEventCallback(fd, e);

}

void TCPConnection::WriteMsg(const std::string &msg) {
    //CallbackHandler e(fd_, this);
    //e.set_write_callback<TCPConnection>(&TCPConnection::WriteCallback);
    //IOLoop::Current()->AddEventCallback(e);
    send(fd_, &msg.front(), msg.size(), 0);

}

void TCPConnection::ReadCallback(int fd, int data) {
    LOG_INFO << from_address_ << " Recv " << data << " bytes data";
    if (data == 0) {
        return;
    }
    std::string msg;
    msg.resize((size_t) data);
    recv(fd, &msg.front(), (size_t) data, 0);
    WriteMsg(handler_->Recv(msg));
}

void TCPConnection::WriteCallback(int fd, int data) {
    throw util::IllegalFunctionError(to_string(fd) + " " + to_string(data));

}

void TCPConnection::CloseCallback(int fd, int data) {
#if defined(DC_DEBUG)
    LOG_DEBUG << "fd" << fd << " Connection disconnected " << data;
#endif
    demoniac::IOLoop::current()->removeEventCallback(fd);
    tcp_server_->RemoveConnection(fd);
    close(fd);

}

}
}