#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;


class CSVReader{

    public:
        int lineProgression = 0;
        string line;
        string csv_path;
        CSVReader(string csv_path)
        {
            csv_path = csv_path;
            csv_file.open(csv_path);
            if (!csv_file)
            {
                cout << "Failed to open record" << endl;
            }
            while (!csv_file.eof())
            {
                getline(csv_file, line);
                lineCount++;
            }
        }

        vector<string> getRow(int lineX)
        {
            reset();
            int count = 0;
            for (int x = 0; x < lineX + 1; x++)
            {
                getline(csv_file, line);
            }
            return seperateRow(line);
        }

        vector<string> getNextRow()
        {
            if (lineProgression >= lineCount)
                lineProgression = 0;
            lineProgressionArray = getRow(lineProgression);
            lineProgression++;
            return lineProgressionArray;
        }

        vector<string> getLineWhere(string what)
        {
            reset();
            int count = 0;
            do
            {
               getline(csv_file, line);
            } while (line.find(what) != string::npos);
            
            return seperateRow(line); 
        }
        
        void resetLineProgession()
        {
            lineProgression = 0;
        }

    private:
        vector<string> lineProgressionArray;
        int lineCount = 0;
        fstream csv_file;
        vector<string> seperateRow(string line)
        {
            vector<string> Row;
            int commaPos = 0;
            int columnLength;
            while (true)
            {
                columnLength = line.find(',', commaPos + 1) - commaPos;
                if (commaPos > 0)
                {
                    Row.push_back(line.substr(commaPos + 1, columnLength));
                }
                else
                {
                    Row.push_back(line.substr(commaPos, columnLength));
                }
                commaPos = line.find(',', commaPos + 1);
                if (commaPos == string::npos)
                    return Row;
            }
        }
        void reset()
        {
            csv_file.clear();
            csv_file.seekg(0,std::ios::beg);
        }

};



int main(int argc, char const *argv[])
{
    string generalLocation = "C:\\Documents and Settings\\";
    string targetLocation = "\\Desktop\\";
    CSVReader record("./records.csv");
    string x = record.getLineWhere("04")[0];
    cout << x << endl;
    return 0;
}