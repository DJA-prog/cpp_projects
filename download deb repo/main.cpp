#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

int main(void)
{
    fstream csv_file;
    string csv_path = "./deb_list.csv";
    csv_file.open(csv_path, ios_base::in);
    if (csv_file)
    {
        cout << "Retrieved CSV content" << endl;
    }else
    {
        cout << "Failed to open CSV file" << endl;
        return 1;
    }
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
    int NL_1 = 0;
    int NL_2 = 0;
    string line = "";
    while (true)
    {
        NL_2 = csv_content.find(0x0A, NL_1 + 1);
        if (NL_2 == -1)
            break;
        line = csv_content.substr(NL_1, NL_2 - NL_1);
        if(line.find(0x0A, 0) != string::npos)
            line.erase(line.find(0x0A, 0),1);

        string ssh_command = "apt-cache depends -i " + line +" | awk '/Depends:/ {print $2}' | xargs  apt-get download && apt-get download " + line;
        cout << ssh_command << endl;
        system(ssh_command.c_str());
        
        NL_1 = NL_2;
    }
}