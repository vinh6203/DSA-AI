#include<iostream>
#define MAX 1000

bool hash[MAX + 1][2];

bool search(int x)
{
    if (x < 0)
    {
        x = -x;
        if (hash[x][1] == 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    if (hash[x][0] == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void insert(int a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        if (a[i] < 0)
        {
            a[i] = -a[i];
            hash[a[i]][1] = 1;
            continue;
        }
        hash[a[i]][0] = 1;
    }
}

int main()
{
    int a[] = {47, 61, 36, 52, 56, 33, 92};
    int n = sizeof(a)/sizeof(int);
    int x;
    std::cin >> x;
    insert(a, n);
    if (search(x) == true)
    {
        std::cout << "Yes";
    }
    else
    {
        std::cout << "No"; 
    }
}