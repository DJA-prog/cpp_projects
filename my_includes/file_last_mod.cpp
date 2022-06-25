#include <iostream>
#include <fstream>

using namespace std;
string command, id;

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

string getLastMod(string path, string sessionId)
{
    string tmp_file = "/tmp/" + sessionId + "_Lastmod";
    command = "stat \'" + path + "\' | grep Modify > " + tmp_file;
    system(command.c_str());
    string mod_datetime = getFileLine(tmp_file);
    string mod_date = mod_datetime.substr(8, 10);
    command = "rm " + tmp_file;
    system(command.c_str());
    return mod_date;
}

void sessionId(string prefix)
{
    srand(time(0));
    id = prefix + to_string(rand());
}

int main(int argc, char const *argv[])
{
    sessionId("last_mod_");
    cout << getLastMod(argv[1], id) << endl;
    return 0;
}
