#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

string * split(string line, char splitter) 
{
    static string field_columns[5];
    int line_length = line.length();
    int NL_pointer = 0;
    for (int i = 0; i < 5; i++)
    {
        NL_pointer = line.find(splitter, 0);
        field_columns[i] = line.substr(0, NL_pointer);
        line.erase(0, NL_pointer + 1);
    }
    return  field_columns;
}

int main(void)
{
    cout << "Computer Name: ";
    string find_phrase = "Student23";
    cin >> find_phrase;

    cout << "0-Computer Name" << endl << "1-username" << endl << "2-IP" << endl << "3-password" << endl << "4-updated" << endl << "5-all" << endl;

    cout << "Return (0 - 5): ";
    int csv_column = 4;
    cin >> csv_column;

    fstream csv_file;
    csv_file.open("list.csv", ios_base::in | ios_base::out);

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
        // cout << line;
        if(line.find(find_phrase) != string::npos)
        {
            // cout << line << endl;
            // cout << line.substr(line.find_last_of(0x2C) + 1, line.length() - line.find_last_of(0x2C)) << endl;
            split_return = split(line, 0x2C);
            if(csv_column == 5)
            {
                for (int i = 0; i < 5; i++)
                {
                    cout << split_return[i] << (char)0x09;
                }
                cout << (char)0x0A;
                
            }else
            {
                cout << split_return[csv_column] << endl;
            }
        }
        NL_1 = NL_2;
    }
    
}