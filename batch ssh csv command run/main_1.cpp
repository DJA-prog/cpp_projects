#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

string * csv_seperate(string field) 
{
    static string field_columns[4];
    int field_length = field.length();
    int NL_pointer = 0;
    for (int i = 0; i < 4; i++)
    {
        NL_pointer = field.find(0x2C, 0);
        field_columns[i] = field.substr(0, NL_pointer);
        field.erase(0, NL_pointer + 1);
    }    
    return  field_columns;
}

int main(void)
{
    unsigned char ch;
    string csv_content = "";
    ifstream csv_file_list;
    csv_file_list.open("./list.csv");
    if (!csv_file_list)
    {
        cout << "Failed to open file" << endl;
    }
    else
    {
        cout << "Opened File for reading" << endl;
        while (true)
        {   
            ch = csv_file_list.get();
            if (csv_file_list.eof())
                break;
            csv_content += ch;
            
        }
    }
    int NL_pointer = 0;
    string *csv_seperated;
    string ssh_command;
    string ssh_return;
    while (true)
    {
        NL_pointer = csv_content.find(0x0A, 0);
        csv_seperated = csv_seperate(csv_content.substr(0, NL_pointer));
        
        ssh_command = "sshpass -p '" + csv_seperated[3] + "' ssh " + csv_seperated[1] + "@" + csv_seperated[2] + " 'sudo apt install typespeed -y & exit'";
        cout << ssh_command << endl;
        ssh_return = system(ssh_command.c_str());
        cout << ssh_return;

        csv_content.erase(0, NL_pointer + 1);
        if (NL_pointer == -1)
            break;
    }

}