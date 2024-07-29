#include <iostream>
#include <Networking/server/tcp_server.h>


int main () {
    
    BCA::TCPServer server {BCA::IPV::V4, 55555};

    server.Run();
    return 0;
} 