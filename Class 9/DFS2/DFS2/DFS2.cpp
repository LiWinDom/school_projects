#include <iostream>
#include <vector>

std::vector<std::vector<bool>> field;
int state = 0;

struct Graph {
    private:std::vector<std::vector<int>> graph;
    private:std::vector<int> DFSvector;
    int size;

    public:void init(int sz) {
        size = sz;
        graph.assign(size, std::vector<int>());
        DFSvector.assign(size, 0);
    }

    public:void convert() {
        for (int i = 0; i < field.size(); ++i) {
            for (int j = 0; j < field[i].size(); ++j) {
                if (field[i][j] == true) {
                    if (i > 0) {
                        if (field[i - 1][j] == true) {
                            graph[i * field[i].size() + j].push_back((i - 1) * field.size() + j);
                        }
                    }
                    if (i < field[i].size() - 1) {
                        if (field[i + 1][j] == true) {
                            graph[i * field[i].size() + j].push_back((i + 1) * field.size() + j);
                        }
                    }
                    if (j > 0) {
                        if (field[i][j - 1] == true) {
                            graph[i * field[i].size() + j].push_back(i * field.size() + j - 1);
                        }
                    }
                    if (j < field.size() - 1) {
                        if (field[i][j + 1] == true) {
                            graph[i * field[i].size() + j].push_back(i * field.size() + j + 1);
                        }
                    }
                }
            }
        }
        return;
    }

    public:void DFS(int v, bool fromDFS = false) {
        if (DFSvector[v] != 0) return;
        DFSvector[v] = -1;
        if (!fromDFS) ++state;
        for (int i = 0; i < graph[v].size(); ++i) {
            DFS(graph[v][i], true);
        }
        DFSvector[v] = state;
        return;
    }
};

int main() {
    int x, y;
    Graph graph;
    
    std::cin >> x >> y;
    field.assign(x, std::vector<bool>(y, false));
    graph.init(x * y);
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            char symbol;
            std::cin >> symbol;
            if (symbol == '#') {
                field[i][j] = true;
            }
        }
    }
    graph.convert();
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            if (field[i][j]) {
                graph.DFS(i * field[i].size() + j);
            }
        }
    }
    std::cout << state;

    return 0;
}