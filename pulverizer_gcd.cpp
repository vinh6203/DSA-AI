#include<iostream>
using namespace std;

int gcd(int a, int b)
{
    if (a == 0)
    {
        return b;
    }
    return gcd(b%a, a); //Euler's Algorithm
                        //time complexity O(log(min(a, b)))
}

int main()
{
    int a, b;
    cin >> a >> b;
    cout << gcd(a, b);
}