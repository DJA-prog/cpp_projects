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

vector<int> getVideoDimentions(string path, string sessionId) // height, width
{
    vector<int> dim;
    string tmp_file = "/tmp/" + sessionId + "_vidDim";
    command = "ffprobe -i \'" + path + "\' -v error -select_streams v:0 -show_entries stream=height -of csv=s=x:p=0 > " + tmp_file;
    // cout << command << endl;
    system(command.c_str());
    dim.push_back(stoi(getFileLine(tmp_file)));
    command = "ffprobe -i \'" + path + "\' -v error -select_streams v:0 -show_entries stream=width -of csv=s=x:p=0 > " + tmp_file;
    // cout << command << endl;
    system(command.c_str());
    dim.push_back(stoi(getFileLine(tmp_file)));
    
    remove(tmp_file.c_str());
    return dim;
}

void sessionId(string prefix)
{
    srand(time(0));
    id = prefix + to_string(rand());
}

int main(int argc, char const *argv[])
{
    sessionId("ffprobe");
    for (int x: getVideoDimentions(argv[1], id))
    {
        cout << x << endl;
    }
    
    return 0;
}
