#include <iostream>
#include <cstring>

using namespace std;


int main(void)
{
    string ssh_go[4]; //pass, username, ip, command
    string ssh_return;

    cout << "Password: ";
    cin >> ssh_go[0];
    cout << endl;

    cout << "Username: ";
    cin >> ssh_go[1];
    cout << endl;

    cout << "IP: ";
    cin >> ssh_go[2];
    cout << endl;

    cout << "command (no spaces): ";
    cin >> ssh_go[3];
    cout << endl;

    string ssh_command = "sshpass -p '" + ssh_go[0] + "' ssh " + ssh_go[1] + "@" + ssh_go[2] + " '" + ssh_go[3] + "'";
    cout << ssh_command << endl;
    ssh_return = system(ssh_command.c_str());
    // system("pause");
    cout << ssh_return;
}