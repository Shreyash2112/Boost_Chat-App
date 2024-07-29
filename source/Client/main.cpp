#include <iostream>
#include <Networking/base.h>

using namespace std;

int main () {
    
    cout << "Hello Client" << endl;
    cout << static_cast<int>(MyEnum::One) << endl;
    return 0;
} 