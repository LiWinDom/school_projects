#include <iostream>
#include <vector>
#include <algorithm>

using ll = long long;

struct Edge {
	ll first, second;
	ll start, finish;
};

struct Graph {
	std::vector<Edge> edges;
	ll size;

	void init(ll sz) {
		size = sz;
		return;
	}

	void read(ll eNum) {
		for (ll i = 0; i < eNum; ++i) {
			ll s, w1, w2, f;
			Edge newEdge;
			std::cin >> s >> w1 >> f >> w2;
			newEdge.first = s - 1;
			newEdge.second = f - 1;
			newEdge.start = w1;
			newEdge.finish = w2;
			edges.push_back(newEdge);
		}
		return;
	}

	ll dkstr(ll s, ll f) {
		std::vector<ll> d(size, 3000000);
		std::vector<bool> used;

		d[s] = 0;
		for (ll i = 0; i < size; ++i) {
			if (i == s) {
				used.push_back(true);
				continue;
			}
			used.push_back(false);
		}

		while (true) {
			ll v = -1;
			ll mini = 3000000;
			for (ll i = 0; i < size; ++i) {
				if (!used[i]) continue;
				for (ll j = 0; j < edges.size(); ++j) {
					if (edges[j].first != i) continue;
					if (!used[edges[j].second]) {
						if (mini > edges[j].finish && d[i] <= edges[j].start) {
							mini = edges[j].finish;
							v = edges[j].second;
						}
					}
				}
			}
			if (v == -1) break;
			used[v] = true;
			d[v] = mini;
		}

		if (d[f] == 3000000) return -1;
		else return d[f];
	}
};

int main() {
	Graph graph;
	ll vNum, eNum, s, f;

	std::cin >> vNum >> s >> f >> eNum;
	graph.init(vNum);
	graph.read(eNum);
	std::cout << graph.dkstr(s - 1, f - 1);

	return 0;
}