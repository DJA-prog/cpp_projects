#include <iostream>

using namespace std;

string command, id;

void sessionId(string prefix)
{
    srand(time(0));
    id = prefix + to_string(rand());
}

void removeTmp(string path)
{
    command = "rm " + path;
    system(command.c_str());
}

int main(int argc, char const *argv[])
{
    sessionId("comics_");
    return 0;
}
