#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

struct Graph {
public:std::vector<std::vector<int>> length;
public:std::vector<std::vector<std::pair<int, int>>> from;
	  //private:std::vector<int> BFSvector;
public:int size;

	  void init(int sz) {
		  size = sz;
		  length.assign(size, std::vector<int>(size, -1));
		  from.assign(size, std::vector<std::pair<int, int>>(size, std::pair<int, int>(-1, -1)));
		  return;
	  }

	  void find(int x1, int y1, int x2, int y2) {
		  if (x1 > 0 && y1 > 1) {

		  }
		  return;
	  }

	  void printWay(int x1, int y1, int x2, int y2) {
		  if (x1 == y1 && x2 == x2) {
			  std::cout << x1 + 1 << ' ' << y1 + 1 << '\n';
			  return;
		  }
		  printWay(x1, y1, from[x2][y2].first, from[x2][y2].second);
		  std::cout << x2 + 1 << ' ' << y2 + 1 << '\n';
		  return;
	  }
};

int main() {
	Graph graph;
	int size, x1, y1, x2, y2;

	std::cin >> size >> x1 >> y1 >> x2 >> y2;
	graph.init(size);
	if (x1 == x2 && y1 == y2) {
		std::cout << 0;
		return 0;
	}
	graph.find(x1 - 1, y1 - 1, x2 - 1, y2 - 1);
	graph.printWay(x1 - 1, y1 - 1, x2 - 1, y2 - 1);

	return 0;
}