#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <climits>
using namespace std;

class Graph {
    private:
        unordered_map<int, unordered_map<int, int>> adjList;

    public:
        Graph() {};

        bool contains_vertex(int u){
            if(adjList.find(u) != adjList.end()){
                return true;
            }
            return false;
        }

        bool contains_edge(int u, int v){
            if(adjList.find(u) != adjList.end() && adjList.at(u).find(v) != adjList.at(u).end()){
                return true;
            }
            return false;
        }

        void addVertex(int u){
            adjList[u];
        }

        void addEdge(int u, int v, int w){
            adjList[u][v] = w;
            adjList[v][u] = w;
        }

        void removeEdge(int u, int v){
            if(contains_edge(u, v)){
                adjList[u].erase(v);
                adjList[v].erase(u);
            }
        }

        void removeVertex(int id){
            if (contains_vertex(id)){
                for(auto& pair : adjList.at(id)){
                    int adj = pair.first;
                    adjList[adj].erase(id);
                }
                adjList.erase(id);
            }
        }

        int numVertices() {
            return adjList.size();
        }

        int getEdgeWeight(int u, int v){
            if(contains_edge(u, v)){
                return adjList[u][v];
            }
            return -1;
        }

        vector<pair<int, int>> primMST() {
            vector<pair<int, int>> mst;

            priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
            vector<bool> seen(numVertices(), false);

            unordered_map<int, int> key;
            for(auto& pair : adjList){
                key[pair.first] = INT_MAX;
            } 

            int top = adjList.begin()->first;
            pq.push({0, top});
            key[top] = 0;

            unordered_map<int, int> parent;
            while(!pq.empty()){
                int u = pq.top().second;
                pq.pop();

                if(!seen[u]){
                    seen[u] = true;

                    if(parent.find(u) != parent.end()){
                        mst.push_back({parent[u], u});
                    }

                    for(auto& i : adjList[u]){
                        int v = i.first;
                        int weight = i.second;
                        if (key[v] > weight) {
                            key[v] = weight;
                            pq.push({key[v], v});
                            parent[v] = u;
                        }
                    }
                }
            }
            return mst;
        }
};

