#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

// string * split(string line, char splitter) 
// {
//     static string field_columns[6];
//     int line_length = line.length();
//     int NL_pointer = 0;
//     for (int i = 0; i < 6; i++)
//     {
//         NL_pointer = line.find(splitter, 0);
//         field_columns[i] = line.substr(0, NL_pointer);
//         line.erase(0, NL_pointer + 1);
//     }
//     return  field_columns;
// }

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

    int csv_content_length = 0;

    fstream csv_file;
    string csv_path = "../csv/list.csv";
    csv_file.open(csv_path, ios_base::in | ios_base::out);
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
    csv_content_length = csv_content.length();
    
    int NL_1 = 0; //first char of new line
    int NL_2 = 0; //next enter (0x0A)
    string line = "";
    int line_length = 0;
    while (true)
    {
        NL_2 = csv_content.find(0x0A, NL_1 + 1);
        if (NL_2 == string::npos) //end loop if end of string
            break;
        line = csv_content.substr(NL_1, NL_2 - NL_1);

        while (line.find(0x0A, 0) != string::npos)
            line.erase(line.find(0x0A, 0),1);

        // if(line.find(0x0A, 0) != string::npos)
        //         line.erase(line.find(0x0A, 0),1);
        if (line.find(find_phrase, 0) != string::npos)
        {  
            line_length = line.length();
            int C_1 = 0;
            int C_2 = 0;
            int row_count = 0;
            int column_length = 0;
            while (true)
            {
                // cout << row_count << " " << csv_column << endl;
                C_2 = line.find(0x2C, C_1 + 1);
                

                if (row_count == csv_column)
                {
                    if (row_count == 0)
                    {
                        cout << "a>>";
                        column_length = line.find(0x2C, C_1 + 1) - C_1 + 1;
                        cout << csv_content.substr(NL_1 + C_1, column_length);
                    }else if (row_count == 5)
                    {
                        cout << "b>>";
                        column_length = line_length - C_1 - 1;
                        cout << csv_content.substr(NL_1 + C_1 + 2, column_length);
                    }else
                    {
                        cout << "c>>";
                        column_length = line.find(0x2C, C_1 + 1) - C_1 - 1;
                        cout << csv_content.substr(NL_1 + C_1 + 2, column_length);
                    }
                    cout << "<<" << endl;
                    break;
                }
                if (C_2 == string::npos)
                    break;
                C_1 = C_2;
                row_count++;
            }
        }
        NL_1 = NL_2;
    }
    
    

}