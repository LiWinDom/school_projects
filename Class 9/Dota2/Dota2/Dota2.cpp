#include <iostream>
#include <vector>
#include <algorithm>

using ll = long long;

uint64_t TIME = 0;

bool sortBySec(const std::pair<int, int>& a, const std::pair<int, int>& b) {
    return (a.second < b.second);
}

struct Graph {
    public:ll size;
    private:std::vector<std::vector<ll>> graph;
    private:std::vector<std::vector<ll>> bGraph;
    private:std::vector<char> DFSvector;
    private:std::vector<char> bDFSvector;
    private:std::vector<std::pair<ll, ll>> leave;
    private:std::vector<std::pair<ll, ll>> bLeave;
    private:std::vector<ll> components;

    public:void init(ll sz) {
        size = sz;
        graph.assign(size, std::vector<ll>());
        bGraph.assign(size, std::vector<ll>());
        DFSvector.assign(size, 'W');
        bDFSvector.assign(size, 'W');
        leave.assign(size, std::pair<ll, ll>());
        components.assign(size, -1);

        return;
    }

    public:void read(ll sz) {
        for (ll i = 0; i < sz; ++i) {
            ll a, b;
            std::cin >> a >> b;
            graph[a - 1].push_back(b - 1);
            bGraph[b - 1].push_back(a - 1);
        }
        return;
    }

    public:void DFS(ll s) {
        if (DFSvector[s] != 'W') return;
        DFSvector[s] = 'G';
        for (ll i = 0; i < graph[s].size(); ++i) {
            DFS(graph[s][i]);
        }
        DFSvector[s] = 'B';
        leave[s].first = s;
        leave[s].second = ++TIME;

        return;
    }

    public:bool bDFS(ll s, ll cmp = -1) {
        if (bDFSvector[s] != 'W') return false;
        bDFSvector[s] = 'G';
        for (ll i = 0; i < bGraph[s].size(); ++i) {
            bDFS(bGraph[s][i], cmp);
        }
        bDFSvector[s] = 'B';
        components[s] = cmp;

        return true;
    }

    public:void findComponents() {
        for (ll i = 0; i < size; ++i) {
            DFS(i);
        }
        std::sort(leave.begin(), leave.end(), sortBySec);
        ll cnt = 0;
        for (ll i = 0; i < size; ++i) {
            if (bDFS(i, cnt)) ++cnt;
        }

        return;
    }

    public:void printComponents() {
        ll cNum = 0;
        for (ll i = 0; i < size; ++i) {
            cNum = std::max(cNum, components[i] + 1);
        }
        std::cout << cNum << '\n';
        for (ll i = 0; i < size; ++i) {
            std::cout << components[i] + 1 << ' ';
        }
        return;
    }
};

int main() {
    Graph graph;
    ll vNum, eNum;

    std::cin >> vNum >> eNum;
    graph.init(vNum);
    graph.read(eNum);
    graph.findComponents();
    graph.printComponents();

    return 0;
}