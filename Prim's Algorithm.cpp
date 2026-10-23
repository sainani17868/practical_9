#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

typedef pair<int, int> pii; // (weight, vertex)

void primMST(int V, vector<vector<pii>>& adj) {
    vector<int> key(V, INT_MAX);
    vector<int> parent(V, -1);
    vector<bool> inMST(V, false);

    priority_queue<pii, vector<pii>, greater<pii>> pq;

    key[0] = 0;
    pq.push(make_pair(0, 0));

    while (!pq.empty()) {
        pii top = pq.top();
        pq.pop();

        int u = top.second;

        if (inMST[u]) continue;
        inMST[u] = true;

        for (int j = 0; j < (int)adj[u].size(); j++) {
            int weight = adj[u][j].first;
            int v = adj[u][j].second;

            if (!inMST[v] && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;
                pq.push(make_pair(key[v], v));
            }
        }
    }

    cout << "Edge \tWeight\n";
    for (int i = 1; i < V; i++)
        cout << parent[i] << " - " << i << "\t" << key[i] << "\n";
}

int main() {
    int V = 5;
    vector<vector<pii>> adj(V);

    // addEdge(u, v, w)
    auto addEdge = [&](int u, int v, int w) {
        adj[u].push_back(make_pair(w, v));
        adj[v].push_back(make_pair(w, u));
    };

    addEdge(0, 1, 2);
    addEdge(0, 3, 6);
    addEdge(1, 2, 3);
    addEdge(1, 3, 8);
    addEdge(1, 4, 5);
    addEdge(2, 4, 7);
    addEdge(3, 4, 9);

    primMST(V, adj);
    return 0;
}
