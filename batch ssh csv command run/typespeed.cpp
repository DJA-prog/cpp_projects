#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

string * split(string line, char splitter) 
{
    static string field_columns[6];
    int line_length = line.length();
    int NL_pointer = 0;
    for (int i = 0; i < 6; i++)
    {
        NL_pointer = line.find(splitter, 0);
        field_columns[i] = line.substr(0, NL_pointer);
        line.erase(0, NL_pointer + 1);
    }
    return  field_columns;
}

int main(void)
{
    string command = "export DISPLAY=:0; xterm typespeed & exit";

    fstream csv_file;
    string csv_path = "../csv/list.csv";
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

    int NL_1 = 0;
    int NL_2 = 0;
    string line = "";
    string *split_return;
    while (true)
    {
        NL_2 = csv_content.find(0x0A, NL_1 + 1);
        if (NL_2 == -1)
            break;
        line = csv_content.substr(NL_1, NL_2 - NL_1);
        if(line.find(0x0A, 0) != string::npos)
            line.erase(line.find(0x0A, 0),1);
        split_return = split(line, 0x2C);
        cout << split_return[0] << split_return[5] << endl;
        if (split_return[5] == "T")
        {
            string ssh_command = "sshpass -p '" + split_return[3] + "' ssh -o StrictHostKeyChecking=no " + split_return[1] + "@" + split_return[2] + " '" + command + "'";
            cout << ssh_command << endl;
            system(ssh_command.c_str());
        }
        

        NL_1 = NL_2;
    }


}