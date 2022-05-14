#include <iostream>
#include <string>

using namespace std;

int main(int argc, char const *argv[])
{
    string ch_start = argv[1];
    int ch_start_int = stoi(ch_start);
    string webpage_count = argv[2];
    int webpage_count_int = stoi(webpage_count);

    for (int i = 0; i < webpage_count_int; i++)
    {
        
        string command = "wget --page-requisites https://www.mangaread.org/manga/martial-peak/chapter-" + to_string(ch_start_int + i) + "/";
        cout << command << endl;
        system(command.c_str());
    }
    
    return 0;
}
