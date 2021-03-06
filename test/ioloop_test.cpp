#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "demoniac/io_loop.h"
#include "event_callback.h"
#include "demoniac/log.h"

#define LISTEN_PORT 8000
#define LISTEN_ADDR "0.0.0.0"

char buffer[1000];


class handler: demoniac::util::EventCallback {


    void read_cb(int fd, int data) {
        read(fd, buffer, data);
        buffer[data + 1] = '\0';
        std::cout << "read_cb fd = " << fd << "data = " << buffer << std::endl;
    }

    void write_cb(int fd, int data) {
        std::cout << "write_cb fd = " << fd << "data = " << data << std::endl;
    }

    void close_cb(int fd, int data) {
        close(fd);
        std::cout << "close_cb fd = " << fd << "data = " << data << std::endl;
    }

}
void accept_cb(int fd, int data) {
    std::cout << "accept_cb fd = " << fd << "data = " << data << std::endl;
    sockaddr_in sock_addr;
    socklen_t sock_addr_len;

    for (int i = 0; i < data; ++i) {
        int coon_fd = accept(fd, (sockaddr *) &sock_addr, &sock_addr_len);
        std::cout << "from " << inet_ntoa(sock_addr.sin_addr) << std::endl;

        std::cout << "add conn " << coon_fd << std::endl;
        demoniac::Event e(coon_fd, nullptr);
        e.set_read_callback(read_cb);
        //e.set_write_callback(write_cb);
        e.set_close_callback(close_cb);
        demoniac::IOLoop::Current()->AddEventCallback(e);
    }
}


int main() {
    int socket_fd, ret;
    sockaddr_in sock_addr;

    socket_fd = socket(PF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0) {
        std::cout << "socket create failed." << std::endl;
        exit(EXIT_FAILURE);
    }

    sock_addr.sin_family = PF_INET;
    sock_addr.sin_port = htons(LISTEN_PORT);
    sock_addr.sin_addr.s_addr = htonl(inet_addr(LISTEN_ADDR));

    ret = ::bind(socket_fd, (sockaddr *) &sock_addr, sizeof(sock_addr));
    if (ret < 0) {
        std::cout << "socket bind failed." << std::endl;
        exit(EXIT_FAILURE);
    }

    ret = listen(socket_fd, 8);
    if (ret < 0) {
        std::cout << "socket listen failed." << std::endl;
        exit(EXIT_FAILURE);
    }

    LOG_DEBUG << "listen fd=" << socket_fd;

    demoniac::CallbackHandler e(socket_fd, nullptr);
    e.set_read_callback(accept_cb);
    e.set_close_callback(close_cb);

    demoniac::IOLoop::Current()->AddEventCallback(e);
    demoniac::IOLoop::Current()->Loop();
    return 0;
}