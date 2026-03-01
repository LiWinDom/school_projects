#include <iostream>
#include <vector>
#include <algorithm>

struct Graph {
    std::vector<std::vector<bool>> graph;
    int sz;

    void init(int s) {
        sz = s;
        graph.assign(sz, std::vector<bool>(sz, false));
        return;
    }

    bool readGraph(int lines) {
        for (int i = 0; i < lines; ++i) {
            int a, b;
            std::cin >> a >> b;
            if (graph[a - 1][b - 1]) return false;
            graph[a - 1][b - 1] = true;
            graph[b - 1][a - 1] = true;
        }
        return true;
    }

    int isFull() {
        for (int i = 0; i < sz; ++i) {
            for (int j = 0; j < sz; ++j) {
                if (i == j) continue;
                if (graph[i][j] == false) return false;
            }
        }
        return true;
    }
};

/*struct Graph {
    std::vector<std::vector<int>> graph;
    int sz;

    void init(int s) {
        sz = s;
        graph.assign(sz, std::vector<int>());
        return;
    }

    void readGraph(int lines) {
        for (int i = 0; i < lines; ++i) {
            int a, b;
            std::cin >> a >> b;
            graph[a - 1].push_back(b - 1);
            graph[b - 1].push_back(a - 1);
        }
        return;
    }
};*/

int main() {
    Graph graph;
    int size, lines;

    std::cin >> size >> lines;
    graph.init(size);
    if (!graph.readGraph(lines)) {
        std::cout << "NO";
    }
    else {
        if (graph.isFull()) {
            std::cout << "YES";
        }
        else {
            std::cout << "NO";
        }
    }

    return 0;
}