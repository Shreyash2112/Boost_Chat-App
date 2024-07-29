#include <iostream>
#include <Networking/base.h>

using namespace std;

int main () {

    MultiplyByThree();
    
    cout << "Hello Server" << endl;
    cout << static_cast<int>(MyEnum::Two) << endl;
    return 0;
} 