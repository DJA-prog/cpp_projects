#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <vector>

using namespace std;

string pathinfo(string url, int file_info) // 0:filepath ; 1:filename ; 2:basename ; 3: fileextention
{
    
    string fileName;
    int last_fslash = url.rfind("/");
    string filePath = url.substr(0, last_fslash); // filepath
    int url_var_sep = 0;
    if (url.rfind("?") != string::npos)
    {
        url_var_sep = url.rfind("?");
    }
    fileName = url.substr(last_fslash + 1, url_var_sep - last_fslash - 1); // filename
    string fileExtention = fileName.substr(fileName.rfind(".") + 1, fileName.length() - fileName.rfind(".")); //fileExtention
    string baseName = fileName.substr(0, fileName.rfind(".")); //basename
    if (file_info == 0)
    {
        return filePath;
    }else
    if (file_info == 1)
    {
        return fileName;
    }else
    if (file_info == 2)
    {
        return baseName;
    }
    return fileExtention;
}

bool file_exists(string path)
{
    fstream myfile;
    myfile.open(path, ios::in);
    if (myfile.is_open())
    {
        myfile.close();
        return true;
    }
    return false;    
}

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

        cout << "####################  CH:" << ch_current << "  ####################" << endl;
        if (remove("index.html") != 0)
        {
            cout << "error deleting / could not find index.html"<< endl;
        }
        command = "wget https://www.mangaread.org/manga/martial-peak/chapter-" + to_string(ch_current) + "/";

        // cout << command << endl;
        system(command.c_str());
        command = "mkdir " + to_string(ch_current);
        // cout << command << endl;
        system(command.c_str());

        vector<string> image_list = getlines();
        int image_list_count = image_list.size();
        int z = 0;

        for (string x: image_list)
        {
            z++;
            cout << "image: " << z << "/" << image_list_count << endl;
            cout << x << endl;
            if (!file_exists(to_string(ch_current) + "/" + pathinfo(x, 1)))
            {
                command = "wget " + x + " -P " + to_string(ch_current);
                // cout << command << endl;
                system(command.c_str());
            }else
            {
                cout << "Image exists" << endl;
            }
        }
    }
    
    return 0;
}
