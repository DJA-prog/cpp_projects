#include <iostream>
#include <time.h>

using namespace std;

int main(void)
{
    time_t local_time;
    struct tm * timeinfo;

    time (&local_time);
    timeinfo = localtime (&local_time);
    cout << time(timeinfo) << endl;
}