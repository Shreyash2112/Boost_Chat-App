#include <Networking/server/tcp_connection.h>
#include <iostream>

namespace BCA
{

    TCPConnection::TCPConnection(boost::asio::ip::tcp::socket&& socket) : _socket(move(socket))
    {
    }

    void TCPConnection::Start()
    {
        auto strongThis = shared_from_this();

        boost::asio::async_write(_socket, boost::asio::buffer(_message),
                                 [strongThis](const boost::system::error_code &error, size_t bytesTransferred)
                                 {
                                     if (error)
                                     {
                                         cout << "Failed to send message! \n";
                                     }
                                     else
                                     {
                                         cout << "Sent " << bytesTransferred << " bytes of data! \n";
                                     }
                                 });

        boost::asio::streambuf buffer;

        _socket.async_receive(buffer.prepare(512), [this](const boost::system::error_code &error, size_t bytesTransferred) {
            if(error == boost::asio::error::eof) {
                // Clean connection cut off
                cout << "Client disconnected properly! \n";
            }
            else if (error)
            {
                cout << "Client disconnected in bad way! \n";
            }  
        });
    }

}
