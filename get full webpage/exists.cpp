#include <fstream>
#include <string>
#include <iostream>

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

int main(int argc, char const *argv[])
{
    string path = argv[1];
    if (file_exists(path))
    {
        cout << "File: " << path << " [ EXISTS ]" << endl;
    }else
    {
        cout << "File: " << path << " [ DOES NOT EXIST ]" << endl;
    }
    
    return 0;
}
