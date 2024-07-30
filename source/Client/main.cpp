#include <Networking/client/tcp_client.h>
#include <iostream>
#include <thread>

using namespace BCA;

int main () {
    
    TCPClient client {"localhost", 55555};

    client.OnMessage = [] (const string& message) {
        cout << message; 
    };

    thread t{[&client] () {client.Run(); }};

    while(true) {
        string message;
        getline(cin, message);

        if (message == "\\q") break;
        message += "\n";

        client.Post(message);
    }

    client.Stop();
    t.join();


    return 0;
} 