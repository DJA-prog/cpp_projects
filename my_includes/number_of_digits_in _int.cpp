int digitsInInt(int n)
{
    int number_of_digits = 0;
    do {
        ++number_of_digits; 
        n /= 10;
    } while (n);
    return 0;
}