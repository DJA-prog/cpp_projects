#include<iostream>
#include<fstream>
#include<string>

using namespace std;

int main(void)
{
    //open file for write
    ofstream csv_write;
    csv_write.open("write.csv", ios_base::app);

    //get string from user
    string fullName;
    cout << "Type your full name: ";
    getline (cin, fullName);
    cout << "Your name is: " << fullName << endl;

    //write string to file
    csv_write << fullName << (char)0x0A;

    csv_write.close();
}