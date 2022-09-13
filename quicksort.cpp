#include<iostream>
using namespace std;

int partition(int* a, int low, int high)
{
    int pivot = a[high];
    int i = low, j = low;
    while (j < high)
    {
        if (a[j] <= pivot)
        {
            swap(a[j], a[i]);
            i++;
        }
        j++;
    }
    swap(a[i], a[high]);
    return i;
}

void quicksort(int* a, int low, int high)
{
    if (low < high)
    {
        int pivot = partition(a, low, high);
        quicksort(a, low, pivot - 1);
        quicksort(a, pivot + 1, high);
    }
    
}

int main()
{
    int a[] = {1, 2, -1, 9, 11, -5, 5, 6, 7};
    quicksort(a, 0, sizeof(a)/sizeof(a[0]));
    for (int i : a)
    {
        cout << i << " ";
    }
}
