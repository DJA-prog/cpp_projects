#include <string>
#include <fstream>

using namespace std;

bool file_exists(string path)
{
    fstream myfile;
    myfile.open(path, ios::in);
    if (myfile.is_open())
    {
        myfile.close();
        return true;
    }
    return false;    
}