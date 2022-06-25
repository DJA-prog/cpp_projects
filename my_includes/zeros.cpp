#include <iostream>

using namespace std;

int digitsInInt(int n)
{
    int number_of_digits = 0;
    do {
        ++number_of_digits; 
        n /= 10;
    } while (n);
    return number_of_digits;
}

string zeros(int value, int digits)
{
    string output = to_string(value);
    int digitCount = digitsInInt(value);
    for (size_t i = 0; i < digits - digitCount; i++)
    {
        output = '0' + output;
    }
    return output;
}

string zeros(string value, int digits)
{
    int digitCount = value.length();
    for (size_t i = 0; i < digits - digitCount; i++)
    {
        value = '0' + value;
    }
    return value;
}