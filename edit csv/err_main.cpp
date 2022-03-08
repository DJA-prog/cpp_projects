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
        //find the first 0x0A, record
        NL_pointer = line.find(splitter, 0); //find comma in input
        //print from 0 to 0x0A - 1
        field_columns[i] = line.substr(0, NL_pointer);
        //erase 0 to 0x0A + 1
        line.erase(0, NL_pointer + 1); //remover from input string first part with comma
    }
    
    return  field_columns; //return array
}

int main(void)
{
    unsigned char ch;
    string csv_content = "";
    string find_phrase = "Student20";

    //open file for edit(read write)
    fstream csv_file;
    csv_file.open("list.csv", ios_base::in | ios_base::out);

    //read data
    if(!csv_file)
        return 1;

     while (true)
    {   
        ch = csv_file.get();
        if (csv_file.eof())
        {
            break;
        }
        csv_content += ch;
    }
    cout << csv_content << endl;
    //process each line
        //seperate into line
        string *line_split;
        string line;
        int NL_pointer = 0;
        while (true)
        {
            NL_pointer = csv_content.find(0x0A, NL_pointer + 1);
            cout << NL_pointer << endl;
            line = csv_content.substr(0, NL_pointer);
            if(line.find(find_phrase, 0) > NL_pointer)
            {
                cout << "Found phrase " << find_phrase << " at " << NL_pointer << endl;
                break;
            }
            line = "";
            // line_split = split(line, 0x0A);

            // csv_content.erase(0, NL_pointer + 1);

            if (NL_pointer == -1)
                break;
        }
        // line.length() - 1;
        // ;
        cout << line << endl;
        cout << line.find_last_of(',', 0) << endl;
        line.replace(line.find_last_of(',', 0)+1, line.length() - line.find_last_of(',', 0), "TRUE");
        cout << line << endl;
        // line_split = split(line, 0x0A);
        // lin
        // int pos_5_length = line_split[4].length();

        //find in the line
    //replace
}