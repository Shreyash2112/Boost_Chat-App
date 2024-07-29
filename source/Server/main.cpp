#include <iostream>
#include <boost/asio.hpp>

using namespace std;
using boost::asio::ip::tcp;

int main () {

    try {

        cout << "Accepting connection on port 55555 \n";
        boost::asio::io_context io_context;

        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 55555));

        while(true) {
            tcp::socket socket(io_context);
            acceptor.accept(socket);

            string hello_message = "Hello, There !! \n";
            boost::system::error_code error;

            boost::asio::write(socket, boost::asio::buffer(hello_message), error); 
        }
    }
    catch (exception& e){
        cerr << e.what() << endl;
    }

    return 0;
} 