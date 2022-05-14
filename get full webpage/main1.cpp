#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <vector>

using namespace std;

vector<string> getlines()
{
    fstream index_file;
    string file_content_line;
    vector<string>  images_list;
    index_file.open("index.html", ios::in);
    if (index_file.is_open()){ 
      	while(getline(index_file, file_content_line)){
              if (file_content_line.find("wp-manga-chapter-img") != string::npos)
              {
                //   cout << file_content_line << endl;
                  string image_url = file_content_line.substr(3, file_content_line.find("class") - 5);
                //   cout << image_url << endl;
                  images_list.push_back(image_url);
              }
      	}
      	index_file.close(); //close the file object.
   	}else{
   		cout << "could not open index.html" << endl;
   	}
    return images_list;
}

int main(int argc, char const *argv[]) // chapter count
{

    string ch_start = argv[1];
    int ch_start_int = stoi(ch_start);
    string webpage_count = argv[2];
    int webpage_count_int = stoi(webpage_count);
    string command;

    for (int i = 0; i < webpage_count_int; i++)
    {
        int ch_current = ch_start_int + i;
        if (remove("index.html") != 0)
        {
            cout << "error deleting / could not find image.html"<< endl;
        }
        command = "wget https://www.mangaread.org/manga/martial-peak/chapter-" + to_string(ch_current) + "/";

        cout << command << endl;
        system(command.c_str());
        command = "mkdir " + to_string(ch_current);
        cout << command << endl;
        system(command.c_str());

        vector<string> image_list = getlines();
        for (string x: image_list)
        {
            cout << x << endl;
            command = "wget " + x + " -P ./" + to_string(ch_current);
            cout << command << endl;
            system(command.c_str());
        }
    }
    
    return 0;
}
