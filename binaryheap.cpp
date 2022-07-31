#include<bits/stdc++.h>
using namespace std;

class MinHeap
{
private:
    int* harr;
    int capacity;
    int heap_size;
public:
    MinHeap(int capacity);

    void MinHeapify(int );

    int parent(int i)
    {
        return (i-1)/2;
    }

    int left_child(int i)
    {
        return (2*i+1);
    }

    int right_child(int i)
    {
        return (2*i+2);
    }

    int get_min()
    {
        return harr[0];
    }

    void decreaseKey(int i, int new_val);

    int extractMin();

    void deleteKey(int i); //delete at index i

    void insertKey(int k); //insert key value "k"
};

MinHeap::MinHeap(int cap)
{
    heap_size = 0;
    capacity = cap;
    harr = new int[cap]; //size of heap = cap
}

void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

void MinHeap::insertKey(int k)
{
    if (heap_size == capacity)
    {
        cout << "\nHeap is full\n";
        return;
    }
    heap_size++;
    int i = heap_size - 1;
    harr[i] = k;

    while (i != 0 && harr[parent(i)] > harr[i])
    {
        swap(&harr[i], &harr[parent(i)]);
        i = parent(i);
    }
    
}

int MinHeap::extractMin()
{
    if (heap_size <= 0)
    {
        return INT_MAX; 
    }
    if (heap_size == 1)
    {
        heap_size--;
        return harr[0];
    }
    int root = harr[0];
    harr[0] = harr[heap_size-1];
    heap_size--;
    MinHeapify(0); //start at index 0
  
    return root;
}

//decreases key value of key at index i to new_val
void MinHeap::decreaseKey(int i, int new_val) 
{                                             
    harr[i] = new_val;
    while (i != 0 && harr[parent(i)] > harr[i])
    {
       swap(&harr[i], &harr[parent(i)]);
       i = parent(i);
    }
}

void MinHeap::deleteKey(int i)
{
    decreaseKey(i, INT_MIN);
    extractMin();
}

void MinHeap::MinHeapify(int i)
{
    int l = left_child(i); //l = index of left child
    int r = right_child(i); //r = index of right child
    int smallest = i; //current node

    // l < heap_size: check whether we are at leaves yet !
    if (l < heap_size && harr[l] < harr[r])
    {
        smallest = l; //make smallest pointer point to l = left_child(i) if 
                      //left_child.key < right_child.key
    }
    if (r < heap_size && harr[r] < harr[l])
    {
        smallest = r; //make smallest pointer point to r = right_child(i) if 
                      //right_child.key < left_child.key
    }
    if (smallest != i) //if one of the above cases happens, recurse on left or right subtree
    {                  //if none of the above cases happens -> base case -> recursion stop

        swap(&harr[i], &harr[smallest]); //swap current root and left/right subtree root before recurse
        MinHeapify(smallest); //recurse on left or right subtree base on above two cases
    }
    
    
}

int main()
{
    MinHeap h(20); //max size of heap = 20
    h.insertKey(10);
    h.insertKey(11);
    h.insertKey(22);
    h.insertKey(-2);
    h.insertKey(1);
    h.insertKey(5);
}