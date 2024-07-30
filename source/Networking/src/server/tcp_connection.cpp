#include <Networking/server/tcp_connection.h>
#include <iostream>

namespace BCA
{

    TCPConnection::TCPConnection(boost::asio::ip::tcp::socket&& socket) : _socket(move(socket)) {
        boost::system::error_code ec;

        stringstream name;
        name << _socket.remote_endpoint();

        _username = name.str();
    }

    
    void TCPConnection::Start(MessageHandler&& messageHandler, ErrorHandler&& errorHandler) {
        _messageHandler = move(messageHandler);
        _errorHandler = move(errorHandler);
        asyncRead();
    }

    void TCPConnection::Post(const string &message) {
        bool queueIdle = _outgoingMessages.empty();
        _outgoingMessages.push(message);

        if (queueIdle){
            asyncWrite();
        }
        
    }

    void TCPConnection::asyncRead() {
        boost::asio::async_read_until(_socket, _streamBuf, "\n", [self = shared_from_this()]
        (boost::system::error_code ec, size_t bytesTransferred) {
            self->onRead(ec, bytesTransferred);
        });
    }

    void TCPConnection::onRead(boost::system::error_code ec, size_t bytesTransferred) {
        if(ec) {
            _socket.close(ec);

            _errorHandler();
            return;
        }

        stringstream message;
        message << _username << ": " << istream(&_streamBuf).rdbuf();
        _streamBuf.consume(bytesTransferred);

        _messageHandler(message.str());
        asyncRead();
    }

    void TCPConnection::asyncWrite() {
        boost::asio::async_write(_socket, boost::asio::buffer(_outgoingMessages.front()), [self = shared_from_this()] (boost::system::error_code ec, size_t bytesTransferred) {self->onWrite(ec, bytesTransferred);});
    }

    void TCPConnection::onWrite(boost::system::error_code ec, size_t bytesTransferred) {
        if(ec) {
            _socket.close(ec);

            _errorHandler();
            return;
        }

        _outgoingMessages.pop();

        if(!_outgoingMessages.empty()) {
            asyncWrite();
        }
    }
}
