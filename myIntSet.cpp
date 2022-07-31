#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class MyIntSet{
public:
    MyIntSet();
    MyIntSet(int a[], int n);
    ~MyIntSet();
    bool insertVal(int v);
    bool eraseVal(int v);
    void clearAll();
    bool findVal(int v) const;
    bool isEmpty() const;
    int getSize() const;
    const int* getBeginPtr() const;
    const int* getEndPtr() const;
    void print();
private:
    int maxSize;
    int* elements;
    int num;
};

MyIntSet::MyIntSet()
{
    maxSize = 0;
    num = 0;
	elements = new int[1000];
	for (int i = 0; i < 1000; i++)
	{
		elements[i] = 0;
	}
}

MyIntSet::MyIntSet(int a[], int n)
{
    elements = new int[1000];
    maxSize = 2*n + 1;
	num = n;
	for (int i = 0; i < num; i++)
	{
		elements[i] = a[i];
	}
}

MyIntSet::~MyIntSet()
{
    delete[] elements;
}

void MyIntSet::print()
{
    for (int i = 0; i < num; i++)
    {
        cout << elements[i] << " ";
    }
    
}

const int* MyIntSet::getBeginPtr() const
{
    const int *ptr = elements;
    return ptr;
}

const int* MyIntSet::getEndPtr() const
{
    int *ptr = elements;
    ptr += num-1;
    return ptr;
}

bool MyIntSet::isEmpty() const
{
    if (num == 0)
    {
        return true;
    }
    return false;
}

void MyIntSet::clearAll()
{
    for (int i = 0; i < num; i++)
    {
        elements[i] = '\0';
    }
    num = 0;
}

bool MyIntSet::findVal(int v) const
{
    for (int i = 0; i < num; i++)
    {
        if (elements[i] == v)
        {
            return true;
        }
        
    }
    return false;
}

bool MyIntSet::insertVal(int v)
{
    if (maxSize == 0)
    {
        maxSize = 0;
    }
    if (findVal(v) == true)
    {
        return false;
    }
    if (num >= maxSize)
	{
		maxSize = 2*maxSize + 1;
	}
	elements[num] = v;
	num += 1;
    return true;
}

bool MyIntSet::eraseVal(int v)
{
    if (findVal(v) == false)
    {
        return false;
    }
    for (int i = 0; i < num-1; i++)
    {
        if (elements[i] == v)
        {
            elements[i] = elements[i+1];
        }
        
    }
    num--;
    
    return true;
}

int main()
{
    int b[] = {9, 6, 2};
    MyIntSet a(b, sizeof(b)/sizeof(int));
    a.insertVal(1);
    a.insertVal(3);
    a.insertVal(4);
    a.insertVal(69);
    a.eraseVal(69);
    a.print();
}