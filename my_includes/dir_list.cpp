#include <iostream>
#include <vector>
#include <fstream>

using namespace std;
string command, id;

void sessionId(string prefix)
{
    srand(time(0));
    id = prefix + to_string(rand());
}

void removeTmp(string path)
{
    command = "rm " + path;
    system(command.c_str());
}

vector<string> getFileLines(string path)
{
    fstream index_file;
    string file_content_line;
    vector<string> list;
    index_file.open(path, ios::in);
    if (index_file.is_open()){ 
      	while(getline(index_file, file_content_line)){
            list.push_back(file_content_line);
      	}
      	index_file.close();
   	}else{
   		cout << "could not open "<< path << endl;
   	}
    return list;
}

vector<string> getDirList(string path, string sessionId)
{
    string tmp_file = sessionId + "_dirList";
    command = "ls \'" + path + "\' > " + tmp_file;
    system(command.c_str());
    vector<string> files = getFileLines(tmp_file);
    removeTmp(tmp_file);
    return files;
}

int main(int argc, char const *argv[])
{
    sessionId("dir_list_");
    for (string x: getDirList(argv[1], id))
    {
        cout << argv[1] + x << endl;
    }
    return 0;
}
