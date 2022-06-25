#include <iostream>
#include <string>

using namespace std;

// string pathinfo(string url, int file_info) // 0:filepath ; 1:filename ; 2:basename ; 3: fileextention
// {
    
//     string fileName;
//     int last_fslash = url.rfind("/");
//     string filePath = url.substr(0, last_fslash); // filepath
//     int url_var_sep = 0;
//     if (url.rfind("?") != string::npos)
//     {
//         url_var_sep = url.rfind("?");
//     }
//     fileName = url.substr(last_fslash + 1, url_var_sep - last_fslash - 1); // filename
//     string fileExtention = fileName.substr(fileName.rfind(".") + 1, fileName.length() - fileName.rfind(".")); //fileExtention
//     string baseName = fileName.substr(0, fileName.rfind(".")); //basename
//     if (file_info == 0)
//     {
//         return filePath;
//     }else
//     if (file_info == 1)
//     {
//         return fileName;
//     }else
//     if (file_info == 2)
//     {
//         return baseName;
//     }
//     return fileExtention;
// }

string pathinfo(string url, int file_info) // 0:filepath ; 1:filename ; 2:basename ; 3: file_extention ; 4: parent_directory
{
    int dot_find;
    int url_length = url.length();
    string filepath, filename, basename, extention, parent_dir;
    if (url.rfind('.') == string::npos)
    {
        dot_find = url_length;
        extention = "";
    }else{
        dot_find = url.rfind('.');
        extention = url.substr(dot_find, url_length - dot_find);
    }

    if (url.rfind('/') == string::npos)
    {
        basename = url.substr(0 , dot_find);
        filename = url;
        filepath = ".";
    }else{
        basename = url.substr(url.rfind('/'), dot_find - url.rfind('/'));
        filename = url.substr(url.rfind('/'), url_length - url.rfind('/'));
        filepath = url.substr(0, url.rfind('/'));
        parent_dir = url.substr(url.rfind('/', url.rfind('/') - 1) + 1, url.rfind('/') - url.rfind('/', url.rfind('/') - 1) - 1);
    }

    switch (file_info)
    {
    case 0:
        return filepath;
        break;
    
    case 1:
        return filename;
        break;

    case 2:
        return basename;
        break;

    case 3:
        return extention;
        break;

    default:
        return parent_dir;
        break;
    }
}


int main(int argc, char const *argv[])
{
    string url = "https://www.youtube.com/index.php?w=302df3ffhf4&s=123";
    
    cout << pathinfo(url, 0) << endl;
    cout << pathinfo(url, 1) << endl;
    cout << pathinfo(url, 2) << endl;
    cout << pathinfo(url, 3) << endl;
    cout << pathinfo(url, 4) << endl;
    
    return 0;
}
