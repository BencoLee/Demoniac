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
