#include<iostream>
#include<vector>
#include<list>
#include<map>
using namespace std;

class graph
{
    int V;
    vector<list<int>> adj;
    map<int, bool> visited;
public:
    graph(int _V);

    void add_edge(int v, int w);

    void BFS(int s);
    
    void DFS(int s);
};

graph::graph(int _V)
{
    this->V = _V;
    adj.resize(_V);
}

void graph::add_edge(int v, int w)
{
    adj[v].push_back(w); //add edge w to v's adjacent list (use v as index for list<int> in vector adj)
}

//BFS traversal from s, s: source node
void graph::BFS(int s)
{
    vector<bool> visited;
    visited.resize(V, false);

    list<int> queue;
    queue.push_back(s);
    
    while (queue.empty() == false)
    {
        s = queue.front();
        cout << s << " ";
        queue.pop_front();

        for (int adjacent: adj[s])
        {
            if (visited[adjacent] == false)
            {
                visited[adjacent] = true; //set this to true to mark that this node has been visited
                queue.push_back(adjacent);
            }
            
        }
    }
}

//DFS traversal from s, s: source node
void graph::DFS(int s)
{
    visited[s] = true; //set this to true to mark that this node has been visited
    cout << s << " ";
    for (list<int>::const_iterator i = adj[s].begin(); i != adj[s].end(); i++)
    {
        if (visited[*i] == false)
        {
            DFS(*i);
        }
        
    }
}

int main()
{
    graph G(10);
    G.add_edge(0, 1);
    G.add_edge(0, 2);
    G.add_edge(0, 3);
    G.add_edge(0, 4);
    G.add_edge(0, 5);
    G.add_edge(1, 3);
    G.add_edge(1, 5);
    G.add_edge(1, 4);
    G.add_edge(2, 6);
    G.add_edge(2, 7);
    //G.BFS(0);
    G.DFS(0);
}