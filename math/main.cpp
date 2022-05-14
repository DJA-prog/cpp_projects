#include <iostream>
#include <math.h>
#include <string>
#include <cstring>

using namespace std;

int main(int argc, char const *argv[]) 
{
    string function = argv[1];
    int a = atoi(argv[2]);
    int b = atoi(argv[3]);
    int c = atoi(argv[4]);

    cout << "Your choice: " << endl;
    cout << "   Function: " << function << endl;
    cout << "   a: " << a << endl;
    cout << "   b: " << b << endl;
    cout << "   c: " << c << endl;
    
    if (function == "quadratic") // quadratic 1 -3 2
    {
        cout << "calculating quadratic..." << endl;
        int answer1 = -b+(sqrt(pow(b, 2) - 4*a*c)/2*a);
        int answer2 = -b-(sqrt(pow(b, 2) - 4*a*c)/2*a);
        cout << "answers: " << answer1 << " : " << answer2 << endl;
    }

    if (function == "power") // power base index null
    {
        cout << "calculating power..." << endl;
        int answer1 = pow(a, b);
        cout << "answer: " << answer1 << endl;
    }
    
    return 0;
}
