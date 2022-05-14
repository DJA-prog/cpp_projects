#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <vector>
#include <unistd.h>

using namespace std;
unsigned int microsecond = 1000000;

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
    fstream test_file;
    test_file.open(path, ios::in);
    if (test_file.is_open())
    {
        test_file.close();
        return true;
    }
    return false;    
}

int connectionCheck()
{
    system("./ping > test.log");
    fstream ping_file;
    string file_content_line;
    string content[5];
    
    ping_file.open("test.log", ios::in);
    if (ping_file.is_open())
    {
        int line_count = 0;
        while (getline(ping_file, file_content_line))
        {
            content[line_count] = file_content_line;
            line_count++;
        }
        int percentage_loss = stoi(content[0]);
        float avg = stof(content[2]);
        float max = stof(content[3]);
        if(percentage_loss < 20 && avg < 80.0 && max < 1000.0)
        {
            return 0;
        }else
        {
            return 1;
        }
    }
    return 0;
}

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

        ping:
        cout << "Checking internet connection..." << endl;
        if(connectionCheck() == 1){
            cout << "Poor internet: waiting 2 minutes" << endl;
            usleep(120 * microsecond);//sleeps for 120 second = 2 minutes
            goto ping;
        }else
        {
            cout << "Internet working well enough" << endl;
        }
        

        cout << "####################  CH:" << ch_current << "  ####################" << endl;

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

            if (file_exists(target_dir + to_string(ch_current) + "/" + pathinfo(x, 1)))
            {
                command = "wget " + x + " -P " + target_dir + to_string(ch_current);
                cout << command << endl;
                system(command.c_str());
            }else
            {
                cout << "Image exists" << endl;
            }
            
        }
    }
    
    return 0;
}
