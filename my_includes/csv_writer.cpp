#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class CSVWriter{ // require: none

    public:
        CSVWriter(string csvFile)
        {
            int append_name = 1;
            while (csv_exists(csvFile))
            {
                csvFile = csvFile + '.' + to_string(append_name);
                append_name++;
            }
            
            csv_file.open(csvFile, std::fstream::app);
            if (!csv_file.is_open())
                cout << "Could not create / open log file: " + csvFile << endl;
        }

        void appendField(string data)
        {
            if (newLine)
            {
                csv_file << data;
            }
            else{
                csv_file << ',' << data;
            }
            newLine = false;
        }  

        void appendField(char data)
        {
            if (newLine)
            {
                csv_file << data;
            }
            else{
                csv_file << ',' << data;
            }
            newLine = false;
        } 

        void appendField(int data)
        {
            if (newLine)
            {
                csv_file << data;
            }
            else{
                csv_file << ',' << data;
            }
            newLine = false;
        }

        void endRow()
        {
            csv_file << endl;
            newLine = true;
        }

        void csvClose()
        {
            csv_file.close();
        }

    private:
        bool newLine = true;
        fstream csv_file;
        bool csv_exists(string path)
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

};


int main(int argc, char const *argv[])
{
    CSVWriter csv("./000");
    csv.appendField("Help");
    csv.endRow();
    for (char x: "Hello There")
    {
        csv.appendField(x);
    }
    csv.csvClose();
    return 0;
}
