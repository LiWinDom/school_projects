#include <iostream>
#include <string>
#include <vector>

struct GraphFull {
    std::vector<std::vector<bool>> graph;
    long long sz;

    void init(long long s) {
        sz = s;
        graph.assign(sz, std::vector<bool>(sz, false));
        return;
    }

    void readGraph() {
        for (long long i = 0; i < sz; ++i) {
            for (long long j = 0; j < sz; ++j) {
                long long num;
                std::cin >> num;
                graph[i][j] = num;
            }
        }
        return;
    }

    void printLines() {
        for (long long i = 0; i < sz; ++i) {
            for (long long j = 0; j < sz; ++j) {
                std::cout << graph[i][j] << ' ';
            }
            std::cout << '\n';
        }
        return;
    }
};

struct GraphOptimize {
    std::vector<std::vector<int>> graph;
    long long sz;

    void init(long long s) {
        sz = s;
        graph.assign(sz, std::vector<int>());
        return;
    }

    void readGraph() {
        std::string buf;
        std::getline(std::cin, buf);

        for (long long i = 0; i < sz; ++i) {
            std::string line;

            std::getline(std::cin, line);
            for (size_t j = 0; j < line.length(); ++j) {
                long long num = 0;
                while (line[j] != ' ') {
                    num = num * 10 + line[j] - '0' - 1;
                    ++j;
                    if (j >= line.length()) {
                        break;
                    }
                }
                graph[i].push_back(num);
            }
        }
        return;
    }

    void rotat() {
        GraphOptimize graphN;

        graphN.init(sz);
        for (long long i = 0; i < sz; ++i) {
            for (size_t j = 0; j < graph[i].size(); ++j) {
                graphN.graph[graph[i][j]].push_back(i);

                long long lol = 0;
                lol = lol + 1;
            }
        }
        graph = graphN.graph;
        return;
    }

    void printLines() {
        for (long long i = 0; i < sz; ++i) {
            for (size_t j = 0; j < graph[i].size(); ++j) {
                std::cout << graph[i][j] + 1 << ' ';
            }
            std::cout << '\n';
        }
        return;
    }
};

int main() {
    long long size;
    GraphOptimize graphO;

    std::cin >> size;
    graphO.init(size);
    graphO.readGraph();
    graphO.rotat();
    std::cout << size << '\n';
    graphO.printLines();

    return 0;
}
