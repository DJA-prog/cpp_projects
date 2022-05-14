#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <vector>

using namespace std;

string command_file_path = "./commands.list";

vector<string> getCommands(string path)
{
    cout << "getting Commands" << endl;
    fstream commands_file;
    string file_content_line;
    vector<string>  commands;
    commands_file.open(path, ios::in);
    if (commands_file.is_open()){ 
      	while(getline(commands_file, file_content_line)){
            commands.push_back(file_content_line);
      	}
      	commands_file.close(); //close the file object.
   	}else{
   		cout << "could not open " << path << endl;
        // return "failed".c_str();
   	}
    return commands;
}

int main(int argc, char const *argv[]) // url chapter count
{

    if (0 < argv[1])
    {
        command_file_path = argv[1];
    }

    vector<string> commands = getCommands(command_file_path);

    int commands_count = commands.size();
    int z = 0;
    for (string command: commands)
    {
        z++;
        cout << "####################  " << z << "/" << commands_count << "  ####################" << endl;
        cout << command << endl;
        system(command.c_str());
    }
    
    return 0;
}
