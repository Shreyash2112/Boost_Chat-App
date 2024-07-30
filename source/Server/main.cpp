#include <iostream>
#include <Networking/server/tcp_server.h>


int main () {
    
    BCA::TCPServer server {BCA::IPV::V4, 55555};

    server.OnJoin = [] (BCA::TCPConnection::pointer server) {
        cout << "User has joined the server : " << server->GetUsername() << endl;
    };

    server.OnLeave = [] (BCA::TCPConnection::pointer server) {
        cout << "User has left the server : " << server->GetUsername() << endl;
    };

    server.OnClientMessage = [&server] (const string& message) {
        server.Broadcast(message);
    };

    server.Run();
    return 0;
} 