#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

int main(void)
{
    //get file as string
    fstream csv_file;
    string csv_path = "./test.txt";
    csv_file.open(csv_path, ios_base::in);
    unsigned char ch;
    string csv_content;
    if(!csv_file)
        return 1;

    while (true)
    {   
        ch = csv_file.get();
        if (csv_file.eof())
            break;
        csv_content += ch;
    }

    csv_file.close();
    
    csv_file.open(csv_path, ios_base::out);

    csv_content.replace(10, 4, "AA");
    cout << csv_content << endl;

    csv_file << csv_content;
    csv_file.close();
    //scan string in segaments divided by 0x0A
    //get in find  start and length of target subsegment
    //replace target part in file string
    //write back into file the file string
}