#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

int main(void)
{
    cout << "Computer Name: ";
    string find_phrase = "Student23";
    cin >> find_phrase;

    cout << "0-Computer Name ; 1-username ; 2-IP ; 3-password ; 4-updated ; 5-active" << endl;

    cout << "Return (0 - 5): ";
    int csv_column = 4;
    cin >> csv_column;

    cout << "New Value: ";
    string new_value = "F";
    cin >> new_value;

    //get file as string
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

    //scan string in segaments divided by 0x0A
    int NL_1 = 0; //first char of new line
    int NL_2 = 0; //next enter (0x0A)
    string line = "";
    int line_length = 0;
    int line_start = 0;
    while (true)
    {
        NL_2 = csv_content.find(0x0A, NL_1 + 1);
        if (NL_2 == string::npos) //end loop if end of string
            break;
        if (NL_1 == 0)
        {
            line_length = NL_2 - NL_1;
            line_start = NL_1;
            line = csv_content.substr(line_start, NL_2 - NL_1);
        }else
        {
            line_length = NL_2 - NL_1 - 1;
            line_start = NL_1 + 1;
            line = csv_content.substr(line_start, NL_2 - NL_1 - 1);
        }
        if (line.find(find_phrase, 0) != string::npos)
        {
            cout << "start at: " << line_start << "\t line length: " << line_length << "\t line: " << line << endl;
            int C_1 = 0; //first char of new column
            int C_2 = 0; //next enter (0x0A)
            string column = "";
            int column_length = 0;
            int column_start = 0;
            int column_count = 0;
            while (true)
            {
                C_2 = line.find(0x2C, C_1 + 1);
                if (C_2 == string::npos) //end loop if end of string
                    break;
                
                if (C_1 == 0)
                {
                    column_length = C_2 - C_1;
                    column_start = C_1;
                    column = line.substr(column_start, C_2 - C_1);
                }else
                {
                    column_length = C_2 - C_1 - 1;
                    column_start = C_1 + 1;
                    column = line.substr(column_start, C_2 - C_1 - 1);
                }
                if (csv_column == column_count)
                {
                    cout << "start at: " << column_start + line_start << "\t column length: " << column_length << "\t column: " << column << endl;
                    csv_content.replace(column_start + line_start, column_length, new_value);
                    break;
                }
                C_1 = C_2;
                column_count++;
            }
        }
        NL_1 = NL_2;
    }

    csv_file.open(csv_path, ios_base::out);
    csv_file << csv_content;
    csv_file.close();
    //get in line find  start and length of target subsegment

    //replace target part in file string
    //write back into file the file string
}