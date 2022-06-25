#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

string command, id;

int digitsInInt(int n)
{
    int number_of_digits = 0;
    do {
        ++number_of_digits; 
        n /= 10;
    } while (n);
    return number_of_digits;
}

string zeros(int value, int digits)
{
    string output = to_string(value);
    int digitCount = digitsInInt(value);
    for (size_t i = 0; i < digits - digitCount; i++)
    {
        output = '0' + output;
    }
    return output;
}

string getFileLine(string path)
{
    fstream index_file;
    string file_content_line;
    index_file.open(path, ios::in);
    if (index_file.is_open()){ 
      	getline(index_file, file_content_line);
      	index_file.close();
   	}else{
   		cout << "could not open "<< path << endl;
   	}
    return file_content_line;
}

string getVideoDuration(string path, string sessionId)
{
    string tmp_file = "/tmp/" + sessionId + "_vidDur";
    command = "ffprobe -i \'" + path + "\' -v quiet -show_entries format=duration -hide_banner -of default=noprint_wrappers=1:nokey=1 >> " + tmp_file;
    // cout << command << endl;
    system(command.c_str());
    int duration = (int) stoi(getFileLine(tmp_file));
    int minutes = duration / 60;
    int hours = minutes / 60;
    int seconds = duration % 60;
    string duration_str = zeros(hours, 2) + ':' + zeros(minutes, 2) + ':' + zeros(seconds, 2);
    remove(tmp_file.c_str());
    return duration_str;
}

void sessionId(string prefix)
{
    srand(time(0));
    id = prefix + to_string(rand());
}

int main(int argc, char const *argv[])
{
    sessionId("ffprobe");
    cout << getVideoDuration(argv[1], id) << endl;
    return 0;
}
