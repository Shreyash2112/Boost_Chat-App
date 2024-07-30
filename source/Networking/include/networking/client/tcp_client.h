#pragma once
#include <boost/asio.hpp>
#include <string>
#include <queue>

namespace BCA {
    using namespace std;

    using MessageHandler = function<void(string)>;

    class TCPClient {
        public:
            TCPClient(const string& address, int port);

            void Run();
            void Stop();
            void Post(const string& message);

        private:
            void asyncRead();
            void onRead(boost::system::error_code ec, size_t bytesTransferred);
            void asyncWrite();
            void onWrite(boost::system::error_code ec, size_t bytesTransferred);
    
        public:
            MessageHandler OnMessage;

        private:
            boost::asio::io_context _ioContext {};
            boost::asio::ip::tcp::socket _socket;

            boost::asio::ip::tcp::resolver::results_type _endpoints;

            boost::asio::streambuf _streamBuf{65536};
            queue<string> _outgoingMessages;
    };

}