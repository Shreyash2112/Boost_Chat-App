#pragma once

#include <boost/asio.hpp>
#include <Networking/server/tcp_connection.h>
#include <iostream>

using namespace std;

namespace BCA
{
    enum class IPV
    {
        V4,
        V6
    };

    class TCPServer
    {
    public:
        TCPServer(IPV ipv, int port);
        int Run();
        
        void Broadcast(const string& message);

    private:
        void StartAccept();

    private:
        IPV _ipVersion;
        int _port;

        boost::asio::io_context _ioContext;
        boost::asio::ip::tcp::acceptor _acceptor;

        vector<TCPConnection::pointer> _connections {};
    };
    
}