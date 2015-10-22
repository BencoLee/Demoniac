#include "demoniac/inet_address.h"


namespace demoniac{

InetAddress::InetAddress(const int &port) {
    addr_.sin_family = PF_INET6;
    addr_.sin_addr.s_addr =
}

}