//
// Created by Neveralso on 15/10/17.
//

#ifndef DEMONIAC_SOCKET_H
#define DEMONIAC_SOCKET_H

namespace demoniac {

class Socket {
public:

    Socket();

    ~Socket();

    int bind(const InetAddress& inet_addr);

    int listen();

    int accept(InetAddress* inet_addr);

    int conenct(const InetAddress& inet_addr);


private:

    int _socket_fd;

    int socket_status_;

    enum SOCKET_STATUS{
        CONNECTING,
        CONNECTED,
        CLOSING,
        CLOSED,
    };

    Socket(const Socket& socket) = delete;
    Socket& operator = (const Socket& socket) = delete;

};

}


#endif //DEMONIAC_SOCKET_H
