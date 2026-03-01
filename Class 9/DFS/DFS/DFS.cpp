#include <iostream>
#include <vector>

struct Graph {
    std::vector<std::vector<bool>> graph;
    std::vector<int> DFSvector;
    int sz;

    void init(int s) {
        sz = s;
        graph.assign(sz, std::vector<bool>(sz, false));
        DFSvector.assign(sz, 0);
    }

    /*void readGraph() {
        for (int i = 0; i < sz; ++i) {
            for (int j = 0; j < sz; ++j) {
                int num;
                std::cin >> num;
                graph[i][j] = num;
            }
        }
        return;
    }*/

    void readGraph(int lines) {
        for (int i = 0; i < lines; ++i) {
            int a, b;
            std::cin >> a >> b;
            graph[a - 1][b - 1] = true;
            graph[b - 1][a - 1] = true;
        }
        return;
    }

    void DFS(int v, char fill) {
        DFSvector[v] = -1;
        for (int i = 0; i < sz; ++i) {
            if (graph[v][i] == true && DFSvector[i] == 0) {
                DFS(i, fill);
            }
        }
        DFSvector[v] = fill;
        return;
    }
};

int main() {
    int size, lines, counter = 0;
    Graph graph;

    std::cin >> size >> lines;
    graph.init(size);
    graph.readGraph(lines);
    for (int i = 0; i < size; ++i) {
        if (graph.DFSvector[i] == 0) {
            ++counter;
            graph.DFS(i, counter);
        }
    }

    std::cout << counter << '\n';

    for (int i = 1; i <= counter; ++i) {
        int cnt = 0;
        for (int j = 0; j < size; ++j) {
            if (graph.DFSvector[j] == i) {
                ++cnt;
            }
        }
        std::cout << cnt << '\n';
        for (int j = 0; j < size; ++j) {
            if (graph.DFSvector[j] == i) {
                std::cout << j + 1 << ' ';
            }
        }
        std::cout << '\n';
    }

    return 0;
}