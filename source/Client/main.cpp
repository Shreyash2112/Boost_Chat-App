#include <iostream>
#include <array>
#include <boost/asio.hpp>

using namespace std;
using boost::asio::ip::tcp;

int main () {
    
    try {
        boost::asio::io_context ioContext;

        tcp::resolver resolver {ioContext};
        auto endpoints = resolver.resolve("127.0.0.1", "55555");

        tcp::socket socket {ioContext};
        boost::asio::connect(socket, endpoints);

        while(true) {
            // Listen for messages
            array<char, 128> buf {};
            boost::system::error_code error;

            size_t len = socket.read_some(boost::asio::buffer (buf), error);

            if(error == boost::asio::error::eof) {
                // Clean connection cutoff
                break;
            }
            else if (error) {
                throw boost::system::system_error(error);
            }

            std::cout.write(buf.data(), len);
        }
    }

    catch (exception& e) {
        cerr << e.what() << endl;
    }

    return 0;
} 