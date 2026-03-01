#include <iostream>
#include <vector>
#include <algorithm>

std::vector<std::vector<int>> backwardEdges;
std::vector<int> state;
const int STATE_NOT_VISITED = 0;
const int STATE_DURING = 1;
const int STATE_VISITED = 2;
const int STATE_IN_CYCLE = 3;
const int STATE_TREE_ROOT = 4;
const int STATE_IN_CYCLE_VISITED = 5;
const int INF = 1000000000;

std::vector<int> getTreeStat(int v) {
    std::vector<int> res = { 1, 0 };
    for (auto child : backwardEdges[v]) {
        if (state[child] == STATE_VISITED) {
            std::vector<int> res2 = getTreeStat(child);
            res[0] += res2[1];
            res[1] += std::max(res2[0], res2[1]);
        }
    }
    return res;
}

int main() {
    int vNum;
    std::cin >> vNum;
    std::vector<int> forwardEdge(vNum + 1, 0);
    backwardEdges.resize(vNum + 1);
    for (int v = 1; v < vNum + 1; ++v) {
        int dis;
        std::cin >> dis;
        forwardEdge[v] = dis;
        if (dis!= -1) {
            backwardEdges[dis].push_back(v);
        }
    }
    int v;
    state.resize(vNum + 1, STATE_NOT_VISITED);
    for (int s = 1; s < vNum + 1; ++s) {
        if (state[s] == STATE_NOT_VISITED) {
            v = s;
            while (true) {
                if (state[v] == STATE_VISITED || state[v] == STATE_IN_CYCLE || state[v] == STATE_TREE_ROOT) {
                    v = s;
                    while (state[v] == STATE_DURING) {
                        state[v] = STATE_VISITED;
                        v = forwardEdge[v];
                    }
                    break;
                }
                else if (state[v] == STATE_DURING) {
                    while (state[v] == STATE_DURING) {
                        state[v] = STATE_IN_CYCLE;
                        v = forwardEdge[v];
                    }
                    v = s;
                    while (state[v] == STATE_DURING) {
                        state[v] = STATE_VISITED;
                        v = forwardEdge[v];
                    }
                    break;
                }
                else {
                    if (forwardEdge[v] == -1) {
                        state[v] = STATE_TREE_ROOT;
                        v = s;
                        while (state[v] == STATE_DURING) {
                            state[v] = STATE_VISITED;
                            v = forwardEdge[v];
                        }
                        break;
                    }
                    else {
                        state[v] = STATE_DURING;
                        v = forwardEdge[v];
                    }
                }
            }
        }
    }
    int ans = 0;
    int maxRootUsed, maxRootUnused;
    for (int s = 1; s < vNum + 1; ++s) {
        if (state[s] == STATE_TREE_ROOT) {
            std::vector<int> res1 = getTreeStat(s);
            maxRootUsed = res1[0]; maxRootUnused = res1[1];
            ans += std::max(maxRootUsed, maxRootUnused);
        }
        else if (state[s] == STATE_IN_CYCLE) {
            v = s;
            std::vector<int> res4 = getTreeStat(v);
            maxRootUsed = res4[0]; maxRootUnused = res4[1];
            int get_prefix_count1 = maxRootUsed;
            int get_prefix_count0 = -INF;
            int not_get_prefix_count1 = -INF;
            int not_get_prefix_count0 = maxRootUnused;
            state[v] = STATE_IN_CYCLE_VISITED;
            while (true) {
                state[v] = STATE_IN_CYCLE_VISITED;
                v = forwardEdge[v];
                if (state[v] == STATE_IN_CYCLE_VISITED) {
                    int cycle_ans = std::max(std::max(get_prefix_count0, not_get_prefix_count1), not_get_prefix_count0);
                    ans += cycle_ans;
                    break;
                }
                std::vector<int> res5 = getTreeStat(v);
                maxRootUsed = res5[0]; maxRootUnused = res5[1];
                int old_get1 = get_prefix_count1;
                int old_get0 = get_prefix_count0;
                int old_not1 = not_get_prefix_count1;
                int old_not0 = not_get_prefix_count0;
                get_prefix_count1 = maxRootUsed + old_get0;
                get_prefix_count0 = maxRootUnused + std::max(old_get0, old_get1);

                not_get_prefix_count1 = maxRootUsed + old_not0;
                not_get_prefix_count0 = maxRootUnused + std::max(old_not0, old_not1);
            }
        }
    }
    std::cout << ans;
}