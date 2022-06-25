#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Logger{ // require: none

    public:
        Logger(string logFile, string title)
        {
            int append_name = 1;
            while (log_exists(logFile))
            {
                logFile = logFile + '.' + to_string(append_name);
                append_name++;
            }
            
            log_file.open(logFile, std::fstream::app);
            if (!log_file.is_open())
                cout << "Could not create / open log file: " + logFile << endl;
            log_file << "Log: " << title << endl;
        }

        void append(string data)
        {
            log_file << data;
        }  
        void append(char data)
        {
            log_file << data;
        } 

        void appendCode(int code)
        {
            if (code == 0)
            {
                log_file << "[ SUCCESS ]";
            }
            else
            {
                log_file << "[ FAILED ]";
            }
            
        }

        void endLine()
        {
            log_file << endl;
        }

        void logClose()
        {
            log_file.close();
        }

    private:
        fstream log_file;
        bool log_exists(string path)
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
    Logger logging("./000", "Test");
    logging.append("Help");
    for (char x: "Hello There")
    {
        logging.append(x);
    }
    logging.logClose();
    return 0;
}
