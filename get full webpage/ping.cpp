#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;
string ping_log_file = "/tmp/ping.log";

vector<string> getReturn()
{
    vector<string> returnVal;
    fstream log_file;
    string file_content_line;
    log_file.open(ping_log_file, ios::in);
    if (log_file.is_open()){ 
      	while(getline(log_file, file_content_line)){
            if(file_content_line.find("Destination Net Unreachable") != string::npos)
            {
                returnVal.push_back("no");
                returnVal.push_back("100");
                returnVal.push_back("0.0");
                returnVal.push_back("0.0");
                returnVal.push_back("0.0");
                return returnVal;
            }else
            {
                returnVal.push_back("yes");
            }
            if(file_content_line.find("packets transmitted") != string::npos)
            {
                string package_success = file_content_line.substr(file_content_line.find(",", file_content_line.find(",")+1), file_content_line.find(",", file_content_line.find(",", file_content_line.find(",")+1)+1) - file_content_line.find(",", file_content_line.find(",")+1));
                returnVal.push_back(package_success.substr(2, package_success.find("%") - 2));
            }
            if(file_content_line.find("rtt") != string::npos)
            {
                string time_readings = file_content_line.substr(23, file_content_line.length() - 4);
                returnVal.push_back(time_readings.substr(0, time_readings.find("/")));
                returnVal.push_back(time_readings.substr(time_readings.find("/") + 1 , time_readings.find("/", time_readings.find("/") + 1) - time_readings.find("/") - 1));
                returnVal.push_back(time_readings.substr(time_readings.find("/", time_readings.find("/") + 1) + 1, time_readings.find("/", time_readings.find("/", time_readings.find("/") + 1) + 1) - time_readings.find("/", time_readings.find("/") + 1) - 1));
            }
      	}
      	log_file.close(); //close the file object.
   	}else{
   		cout << "could not open " << ping_log_file << endl;
   	}

    return  returnVal;
}

int main(int argc, char const *argv[])
{
    string command = "ping -c 10 8.8.8.8 > " + ping_log_file;
    system(command.c_str());
    vector<string> pingReturn = getReturn();
    for(string x: pingReturn)
    {
        cout << x << endl;
    }
    return 0;
}
