#include <iostream>
#include "networking/listener.h"
using namespace std;
int main() {
    std::cout << "Hello, World!" << std::endl;
    listener listener;
    listener.start("192.168.1.30", "4444");
    return 0;
}
