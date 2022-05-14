#include <iostream>
#include <string>

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

int main(int argc, char const *argv[])
{
    string url = "https://www.youtube.com/index.php?w=302df3ffhf4&s=123";
    
    cout << pathinfo(url, 0) << endl;
    cout << pathinfo(url, 1) << endl;
    cout << pathinfo(url, 2) << endl;
    cout << pathinfo(url, 3) << endl;
    
    return 0;
}
