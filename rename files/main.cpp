// replace %20 in file names with ' ' (space)

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char const *argv[])
{
    system("ls > /tmp/ls.txt");
    fstream index_file;
    string file_content_line;
    index_file.open("/tmp/ls.txt", ios::in);
    if (index_file.is_open()){ 
      	while(getline(index_file, file_content_line)){
            string newName = file_content_line;
            size_t pos;
            while ((pos = newName.find("%20")) != std::string::npos) {
                newName.replace(pos, 3, " ");
            }
            newName.replace(0, 13, "");
            string command = "mv " + file_content_line + " \"" + newName + "\"";
            cout << command << endl;
            system(command.c_str());
      	}
      	index_file.close(); //close the file object.
   	}else{
   		cout << "could not open /tmp/ls.txt" << endl;
   	}
    return 0;
}
