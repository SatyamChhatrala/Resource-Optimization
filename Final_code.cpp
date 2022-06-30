#include<bits/stdc++.h>

using namespace std;

const int maxN=1e5;

vector<string> airports;  // stores list of Airports
unordered_map<string,int> mp;  //stores Airport's index in vector airports
vector<vector<int>> graph;   // adjacency list of existing flight network
vector<bool> vis(maxN);  //To check if Airport is visited or not
vector<int> disc(maxN);  // stores discovery time
vector<int> low(maxN);   // low[v] represents node with earliest discovery time reachable from v
vector<bool> stackMem(maxN);  // represents if node-v is present in stack-st or not.
stack<int> st;
int timer=0; // current time
vector<int> repNode;   //rep[u] is representative node of connected component in which node-u is present


void Tarjans(int u)  // implementation of Tarjan's Algorithm using DFS
{
    vis[u]=true;
    disc[u]=low[u]=timer++;
    stackMem[u]=true;
    st.push(u);

    for(auto v:graph[u])
    {
        if(!vis[v])
        {
            Tarjans(v);
            low[u]=min(low[u],low[v]);
        }
        else if(stackMem[v])
            low[u]=min(low[u],disc[v]);
    }

    if(low[u]==disc[u])
    {
        while(st.top()!=u)
        {
            stackMem[st.top()]=false;
            repNode[st.top()]=u;
            st.pop();
        }

        stackMem[u]=false;
        repNode[u]=u;
        st.pop();
    }

}

int main()
{
    cout<<"Total Number of Airports: "<<endl;
    long n;
    cin>>n;

    cout<<"List of Airport: "<<endl;

    airports.resize(n);
    graph.resize(n);

    for(int i=0;i<n;i++)
    {
        cin>>airports[i];
        mp[airports[i]]=i;
    }

    cout<<"Starting Airport is Monaco Airport: MNC "<<endl;

    cout<<"Total number of existing Flight routes: "<<endl;
    long m;
    cin>>m;

    cout<<"List Flight routes: "<<endl;
    //forming adjacency list of existing flight-network graph
    while(m--)
    {
        string l,r;
        cin>>l>>r;

        graph[mp[l]].push_back(mp[r]);
    }


    repNode.resize(n);

    for(int i=0;i<n;i++)
    {
        if(!vis[i])
        {
            Tarjans(i);
        }
    }

    vector<int> indeg(n,0); //stores in-deg of representative node of each connected component in compressed graph
    //in-degree of node is equal to all incoming edges

    vector<vector<int>> compGraph(n); // adjacency list of compressed graph
    for(int u=0;u<n;u++)
    {
        for(auto v:graph[u])
        {
            if(repNode[u]!=repNode[v])
            {
                compGraph[repNode[u]].push_back(repNode[v]);
                indeg[repNode[v]]++;
            }
        }
    }

    //output
    cout<<"New flight routes to be added: "<<endl;
    long cnt=0;
    for(int i=0;i<n;i++)
    {
        if(repNode[i]==i && indeg[i]==0)
        {
            cout<<"MNC "<<airports[i]<<endl;
            cnt++;
        }
    }

    cout<<"Count of new flight routes added: "<<cnt<<endl;

    return 0;
}
