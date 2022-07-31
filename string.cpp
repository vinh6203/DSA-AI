#include<iostream>
using namespace std;

class String
{
private:
    int n;
    char *str;
public:
    String();
    String(const char*);
    ~String();
    void print();
    void append(const char* a);
};

String::String()
{
    str = (char*)malloc(sizeof(char)*1000);
    for (int i = 0; i < 1000; i++)
    {
        *(str+i) = '\0';
    }
}

String::String(const char* p)
{
    n = 0;
    str = (char*)malloc(sizeof(char)*1000);
    for (const char *ptr = p; *ptr != '\0'; ptr++)
    {
        if (*ptr == '"')
        {
            break;
        }
        *(str+n) = *ptr;
        n++;
    }
    *(str+n) = '\0';
}

String::~String()
{
    delete[] str;
}

void String::print()
{
    for (char *p = str; *p != '\0'; p++)
    {
        if (*p == 'H' && n > 25)
        {
            cout << "h";
            continue;
        }
        cout << *p;
    }
    cout << endl;
}

void String::append(const char* a)
{
    *(str+n) = ' ';
    n++;
    for (const char *p = a; *p != '\0'; p++)
    {
        if (*p == '"')
        {
            break;
        }
        *(str+n) = *p;
        n++;
    }
    *(str+n) = '\0';
}

int main()
{
    
}