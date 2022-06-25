#include <iostream>
#include<unistd.h>

using namespace std;
unsigned int microsecond = 1000000;

int main() {
    cout << "hello" << endl;
    usleep(3 * microsecond);//sleeps for 3 second
    cout << "bye" << endl;
}