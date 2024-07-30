#include <Networking/server/tcp_server.h>

using boost::asio::ip::tcp;

namespace BCA
{
    TCPServer::TCPServer(IPV ipv, int port) : _ipVersion(ipv), _port(port),
                                              _acceptor(_ioContext, tcp::endpoint(_ipVersion == IPV::V4 ? tcp::v4() : tcp::v6(), _port))
    {
    }

    int TCPServer::Run()
    {
        try
        {
            StartAccept();
            _ioContext.run();
        }
        catch (exception &e)
        {
            cerr << e.what() << endl;
            return -1;
        }
        return 0;
    }

    void TCPServer::Broadcast(const string &message)
    {
    }

    void TCPServer::StartAccept()
    {
        // TODO : Create a connection

        _socket.emplace(_ioContext);

        // Asynchronously accept the connection
        _acceptor.async_accept(*_socket, [this](const boost::system::error_code &error){
            
            auto connection = TCPConnection::Create(move(*_socket));

            _connections.insert(connection);
        
            if (!error) 
            {
                connection->Start();
            }

            StartAccept(); });
    }

}
