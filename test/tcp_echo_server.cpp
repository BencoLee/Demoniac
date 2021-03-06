#include <iostream>
#include <cstring>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "demoniac/io_loop.h"
#include "demoniac/tcp/tcp_server.h"
#include "demoniac/tcp/tcp_handler.h"

#define LISTEN_PORT 8002
#define LISTEN_ADDR "0.0.0.0"

class EchoHandler : demoniac::tcp::TCPHandler {
private:
    const static int BUFFER_SIZE = 200;
    char buffer_[BUFFER_SIZE];
public:
    EchoHandler() : TCPHandler() {};
    std::string Recv(const std::string msg) {
        time_t te = time(NULL);
        strftime(buffer_, BUFFER_SIZE, "%m-%d-%Y %H:%M:%S  hi \0", gmtime(&te));
        std::string s(buffer_);
        s+=msg;
        s+="\n";
        std::cout<<s<<endl;

        return s;
    }
};

int main() {

    char buf[50];
    getcwd(buf, sizeof(buf));
    std::cout<<buf<<endl;

    sockaddr_in in_addr;
    in_addr.sin_family = PF_INET;
    in_addr.sin_port = htons(LISTEN_PORT);
    in_addr.sin_addr.s_addr = htonl(inet_addr(LISTEN_ADDR));
    sockaddr sock_addr;
    memcpy(&sock_addr, &in_addr, sizeof(in_addr));
    demoniac::tcp::TCPServer *tcp_server = new demoniac::tcp::TCPServer();
    tcp_server->addHandler<EchoHandler>(*((sockaddr *) &in_addr));
    demoniac::IOLoop::Current()->Start();
    return 0;
}