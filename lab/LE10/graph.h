#include <iostream>
#include <vector>
#include <list>
#include <climits>
#include <queue>
#include <unordered_set>
using namespace std;

class Graph {
    private:
        int n;
        typedef pair<int, int> Edge;
        vector<list<Edge>> v;
        
    public:
        Graph(int size = 2) {
            n = size;
            v.resize(n);
        }

        void addEdge(int x, int y, int w) {
            v[x].push_back({y, w});
            v[y].push_back({x, w});
        }

        void print() {
            for(int i = 0; i < n; i++) {
                cout << "Node " << i << " is connected to: ";
                for (pair<int,int> j : v[i]) {
                    if(j.first != -1){
                        cout << j.first << " : "<< j.second<<", ";
                    }
                }
                cout << endl;
            }
        }

        vector<pair<int, int>> dijkstra(int startNode) {
            priority_queue<Edge, vector<Edge>, greater<Edge>> pq;

            vector<pair<int, int>> ans(n);
            vector<int> dist(n, INT_MAX);
            vector<int> prev(n, -1);
            pq.push({0, startNode});
            dist[startNode] = 0;

            while(!pq.empty()){
                int u = pq.top().second;
                int d = pq.top().first;
                pq.pop();
                if(d > dist[u]){
                    continue;
                }

                for(auto& edge : v[u]){
                    int adj = edge.first;
                    int weight = edge.second;
                    if(dist[u] + weight < dist[adj]){
                        dist[adj] = dist[u] + weight;
                        pq.push({dist[adj], adj});
                        prev[adj] = u;
                    }
                }
            }

            
            for(int i = 0; i < n; ++i){
                ans[i] = {dist[i], prev[i]};
            }
            return ans;
    }

string printShortestPath(int startNode, int endNode) {
    vector<pair<int, int>> p = dijkstra(startNode);

    if (p[endNode].first == -1){
        return "";
    }

    string path = "";
    for (int at = endNode; at != -1; at = p[at].second) {
        path = to_string(at) + " " + path;
        if (at == startNode) {
            break;
        }
    }

    if(!path.empty() && path.substr(0, to_string(startNode).length()) != to_string(startNode)){
        return "";
    }
    return path;
}



};



