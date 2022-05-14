#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <vector>

using namespace std;

vector<string> getlines(string target)
{
    fstream index_file;
    string file_content_line;
    vector<string>  images_list;
    string path = target + "index.html";
    index_file.open(path, ios::in);
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
   		cout << "could not open " + target +"index.html" << endl;
   	}
    return images_list;
}

int main(int argc, char const *argv[]) // url chapter count /target/directory/
{

    string url = argv[1];
    string ch_start = argv[2];
    int ch_start_int = stoi(ch_start);
    string webpage_count = argv[3];
    int webpage_count_int = stoi(webpage_count);
    string target_dir = argv[4];
    string command;

    string url_start = url.substr(0, url.find("####"));
    string url_end = url.substr(url.find("####") + 4, url.size()-url.find("####") + 3);

    for (int i = 0; i < webpage_count_int; i++)
    {
        int ch_current = ch_start_int + i;
        cout << "####################  " << ch_current << "  ####################" << endl;

        string index_path = target_dir + "index.html";
        if (remove(index_path.c_str()) != 0)
        {
            cout << "error deleting / could not find " + target_dir + "index.html"<< endl;
        }
        command = "wget " + url_start + to_string(ch_current) + url_end + " --output-document=\"" + target_dir + "index.html\"";
        cout << command << endl;
        system(command.c_str());

        command = "mkdir " + target_dir + to_string(ch_current);
        cout << command << endl;
        system(command.c_str());

        vector<string> image_list = getlines(target_dir);
        int image_list_count = image_list.size();
        int z = 0;
        for (string x: image_list)
        {
            z++;
            cout << "image: " << z << "/" << image_list_count << endl;
            cout << x << endl;
            command = "wget " + x + " -P " + target_dir + to_string(ch_current);
            cout << command << endl;
            system(command.c_str());
        }
    }
    
    return 0;
}
