#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<string> getFileLines(string path, string filter)
{
    fstream index_file;
    string file_content_line;
    vector<string> list;
    index_file.open(path, ios::in);
    if (index_file.is_open()){ 
      	while(getline(index_file, file_content_line)){
              if (file_content_line.find(filter) != string::npos)
              {
                list.push_back(file_content_line);
              }
      	}
      	index_file.close();
   	}else{
   		cout << "could not open "<< path << endl;
   	}
    return list;
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