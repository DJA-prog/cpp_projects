#include <iostream>
#include <fstream>
// #include <string>
#include <cstring>

using namespace std;

string rasp_ip_list = "/tmp/rasp";
string temp_file = "/tmp/AS_temp";
string target_ip_range = "192.168.178";

int is_file_blank(string file_path)
{
	ifstream checkFile(file_path);
	if(!checkFile) return 0; // cannot open
	if (checkFile.peek() == EOF)
	{
		return 1; // is empty
	}else{
		return 2; // has content
	}
}

int int main(int argc, char const *argv[])
{
	string nmap_command="nmap -sn " + ip_range + ".0/24 | grep raspberrypi > " + rasp_ip_list;
	system(nmap_command);
	return 0;
}