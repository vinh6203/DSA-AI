#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int knapsack_solve(vector<int> weight, vector<int> value, int knapsack_size)
{
    vector<int> a (knapsack_size + 1, 0);
    for (int i = 1; i <= weight.size(); i++) //iterate through all weight list
    {
        for (int j = knapsack_size; j >= 0; j--) //for each size of the bag (knapsack) calculate the optimal "best" solution
        {
            if (j - weight[i-1] >= 0)
            {
                a[j] = max(a[j], a[j-weight[i-1]] + value[i-1]); //j - weight[i-1]: the "best" postition at j - weight[i-1] + corresponding value of i-1 
            }
        }
    }
    /*for (int i : a)
    {
        cout << i << " ";
    }*/
    return *(a.rbegin());
}

int main()
{
    vector<int> value { 60, 100, 120 };
    vector<int> weight { 1, 2, 3 };
    int knapsack_size = 5;
    cout << knapsack_solve(weight, value, knapsack_size); //220
}
