#pragma once
#include <string>
#include <boost/asio.hpp>
#include <memory>
#include <queue>

using namespace std;

namespace BCA {
    using boost::asio::ip::tcp;

    using MessageHandler = function<void(string)>;
    using ErrorHandler = function<void()>;
    class TCPConnection : public enable_shared_from_this<TCPConnection> {
        public:

            using pointer = shared_ptr<TCPConnection>;

            static pointer Create(boost::asio::ip::tcp::socket&& socket) {
                return pointer(new TCPConnection(move(socket)));
            }

            inline const string& GetUsername() const {return _username;}


            tcp::socket& socket() {
                return _socket;
            }

            void Start (MessageHandler&& messageHandler, ErrorHandler&& errorHandler);

            void Post(const string& message);

        private:
            explicit TCPConnection(boost::asio::ip::tcp::socket&& socket);

            // Wait for a new message from client
            void asyncRead();
            void onRead(boost::system::error_code ec, size_t bytesTransferred);

            void asyncWrite();
            void onWrite(boost::system::error_code ec, size_t bytesTransferred);
        
        private:
            tcp::socket _socket;
            string _username;
            
            queue<string> _outgoingMessages;
            boost::asio::streambuf _streamBuf {65536};

            MessageHandler _messageHandler;
            ErrorHandler _errorHandler;
    };
}