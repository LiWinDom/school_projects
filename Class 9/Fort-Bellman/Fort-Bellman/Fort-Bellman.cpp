#include <iostream>
#include <algorithm>
#include <vector>
#include <limits>

using ll = long long;

struct Edge {
    ll first, second;
    ll weight;
};

struct Graph {
    std::vector<Edge> edges;
    std::vector<ll> d;
    ll size;

    void init(ll sz) {
        size = sz;
        d.assign(size, 3000000);

        return;
    }

    void read() {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {

            }
        }
    }

    ll FortBel(ll s, ll f, ll left) {
        d[s] = 0;
        for (int i = 0; i < left; ++i) {
            bool changed = false;
            for (int j = 0; j < edges.size(); ++j) {
                if (d[edges[j].first] != 3000000) {
                    d[edges[j].second] = std::min(d[edges[j].second], d[edges[j].first] + edges[j].weight);
                    changed = true;
                }
            }
            if (!changed) break;
        }
        if (d[f] == 3000000) return -1;
        else return d[f];
    }

    void loopCheck() {
        vector<int> d(n, INF);
        d[v] = 0;
        vector<int> p(n, -1);
        int x;
        for (int i = 0; i < n; ++i) {
            x = -1;
            for (int j = 0; j < m; ++j)
                if (d[e[j].a] < INF)
                    if (d[e[j].b] > d[e[j].a] + e[j].cost) {
                        d[e[j].b] = max(-INF, d[e[j].a] + e[j].cost);
                        p[e[j].b] = e[j].a;
                        x = e[j].b;
                    }
        }

        if (x == -1)
            cout << "No negative cycle from " << v;
        else {
            int y = x;
            for (int i = 0; i < n; ++i)
                y = p[y];

            vector<int> path;
            for (int cur = y; ; cur = p[cur]) {
                path.push_back(cur);
                if (cur == y && path.size() > 1)  break;
            }
            reverse(path.begin(), path.end());

            cout << "Negative cycle: ";
            for (size_t i = 0; i < path.size(); ++i)
                cout << path[i] << ' ';
        }
    }
};

int main() {
    Graph graph;
    ll vNum;

    std::cin >> vNum;;
    graph.init(vNum);
    graph.read();

    graph.loopCheck();

    return 0;
}