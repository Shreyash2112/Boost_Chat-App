#pragma once
#include <string>
#include <boost/asio.hpp>
#include <memory>

using namespace std;

namespace BCA {
    using boost::asio::ip::tcp;
    class TCPConnection : public enable_shared_from_this<TCPConnection> {
        public:

            using pointer = shared_ptr<TCPConnection>;

            static pointer Create(boost::asio::ip::tcp::socket&& socket) {
                return pointer(new TCPConnection(move(socket)));
            }

            tcp::socket& socket() {
                return _socket;
            }

            void Start ();

        private:
            explicit TCPConnection(boost::asio::ip::tcp::socket&& socket);
        
        private:
            tcp::socket _socket;
            string _message {"Hello, There !! \n"};  
    };
}