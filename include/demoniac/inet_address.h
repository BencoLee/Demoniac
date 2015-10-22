#include <string>

#include "netinet/in.h"


namespace demoniac{
class InetAddress {
public:

    InetAddress(const std::string& addr, const int& port);

    InetAddress(const int& port);

private:

    struct sockaddr_in addr_;

    InetAddress() = delete;
}
}
