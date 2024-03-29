#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

string command_return_file_path = "/tmp/returnFile";
string file_path = "/tmp/rasp";
string ip_file_path = "/tmp/ip";
string file_content_line, _file_content_line;
string remove_phrase = "Nmap scan report for raspberrypi.whs.local ";
string ip;
string my_ip;
string ip_range = "192.168.144";
string host_name = "pi";
string username = "pi";
string password = "12345";
string nmap_command;
fstream newfile, idFile;

int idChangedCheck(string command_return_file_path, string _ip)
{
	cout << "Checking for \"WARNING: REMOTE HOST IDENTIFICATION HAS CHANGED!\"\n";
	ifstream read(command_return_file_path);

	if(!read) return 0;

	bool isEmpty = read.peek() == EOF;
	if (isEmpty)
	{
		string command = "ssh-keygen -f \"/home/" + host_name + "/.ssh/known_hosts\" -R \"" + _ip + "\"";
		system(command.c_str());
		cout << "	EMPTY" << endl;
		return 2;
	}else
	{
		cout << "	PASS" << endl;
	}
	
	return 0;
}


int main(void)
{

	cout << "Removing old files..." << endl;
	if (remove(file_path.c_str()) != 0)
	{
		// cout << "error deleting / could not find " << file_path << endl;
	}

	if (remove(ip_file_path.c_str()) != 0)
	{
		// cout << "error deleting / could not find " << ip_file_path << endl;
	}

	if (remove(command_return_file_path.c_str()) != 0)
	{
		// cout << "error deleting / could not find " << command_return_file_path << endl;
	}
	cout << "	Done" << endl;

	cout << "Searching for raspberrypi devices..." << endl;
	nmap_command="nmap -sn " + ip_range + ".0/24 | grep raspberrypi >> " + file_path;
	system(nmap_command.c_str());
	cout << "	Done" << endl;

	cout << "Getting current device ip..." << endl;
	string ip_command = "ip -f inet address | grep " + ip_range + ". >> " + ip_file_path;
	system(ip_command.c_str());

	newfile.open(ip_file_path, ios::in);
	if (newfile.is_open()){ 
      	while(getline(newfile, file_content_line)){
      		string my_ip_temp = file_content_line.substr(9,15);
      		for (int i = 0; i < (unsigned)strlen(my_ip_temp.c_str()); ++i)
      		{
      			if(my_ip_temp[i] != '/')
      			{
      				my_ip += my_ip_temp[i];
      			}
      		}
      		cout << my_ip << endl;
      	}
      	newfile.close(); //close the file object.
   	}else{
   		cout << "could not open " << file_path << endl;
   	}
	cout << "	Done" << endl;

	cout << "Sending shutdown commands..." << endl;
	newfile.open(file_path, ios::in); // open file for read
	if (newfile.is_open()){   //checking whether the file is open
		int line_count = 0;
      	while(getline(newfile, file_content_line)){ //read data from file object and put it into string.
      		file_content_line = file_content_line.replace(0, (unsigned)strlen(remove_phrase.c_str()), "");
      		ip = "";
      		for (int i = 0; i < (unsigned)strlen(file_content_line.c_str()); ++i)
      		{
      			if(file_content_line[i] != '(' && file_content_line[i] != ')'  )
      			{
      				ip += file_content_line[i];
      			}
      		}
      		if (ip != my_ip)
      		{
      			cout << line_count << ": " << ip << endl; //print the data of the string
      			string ssh_command = "sshpass -p '" + password + "' ssh -o StrictHostKeyChecking=no " + username + "@" + ip + " 'cat /sys/firmware/devicetree/base/serial-number > '" + command_return_file_path +"'";
	            cout << ssh_command << endl;
	            system(ssh_command.c_str());
				int checkpass = idChangedCheck(command_return_file_path, ip);
				if(checkpass == 2)
				{
					system(ssh_command.c_str());
				}
        		line_count++;
      		}
        	
      	}
      	newfile.close(); //close the file object.
   	}else{
   		cout << "could not open " << file_path << endl;
   	}
	cout << "	Done" << endl;

	return 0;
}
