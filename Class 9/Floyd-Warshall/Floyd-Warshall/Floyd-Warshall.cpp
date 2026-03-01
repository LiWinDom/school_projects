#include <iostream>
#include <algorithm>
#include <vector>

using ll = double;

struct Graph {
	std::vector<std::vector<ll>> d;
	//std::vector<std::vector<std::pair<ll, ll>>> graph;
	ll size;

	void init(ll sz) {
		size = sz;
		d.assign(size, std::vector<ll>(size, 10000000));
		//graph.assign(size, std::vector<std::pair<ll, ll>>());
		return;
	}

	void read(ll eNum) {
		for (ll i = 0; i < eNum; ++i) {
			ll u, v, w;
			std::cin >> u >> v >> w;
			d[u - 1][v - 1] = w / 100;
			d[v - 1][u - 1] = w / 100;
		}
		return;
	}

	void floyd() {
		for (ll k = 0; k < size; ++k) {
			for (ll i = 0; i < size; ++i) {
				for (ll j = 0; j < size; ++j) {
					if (d[i][k] == 10000000 || d[k][j] == 10000000) continue;
					if (i == j) continue;
					ll x = 1 - (1 - d[i][k]) * (1 - d[k][j]);
					if (d[i][j] > x) {
						d[i][j] = x;
					}
				}
			}
		}
		return;
	}
};

int main() {
	Graph graph;
	ll vNum, eNum, s, f;
	
	std::cin >> vNum >> eNum >> s >> f;
	graph.init(vNum);
	graph.read(eNum);
	graph.floyd();
	std::cout << graph.d[s - 1][f - 1];
	return 0;
}

//p = 1 - (1 - p1)(1 - p2)(1 - p3)...(1 - pk)