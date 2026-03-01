#include <iostream>
#include <iomanip>
#include <algorithm>
#include <limits>

double formulaCount(const double& x) {
	return 2 / std::pow((1 - x), 3);
}

double taylorCount(const double& x) {
	double ans = 2, pastResult = 2;
	uint64_t counter = 2;

	while (true) {
		double curResult = pastResult / (counter - 1) * (counter + 1) * x;
		if (ans + curResult == ans || counter == 0) break;
		ans += curResult;
		pastResult = curResult;
		++counter;
	}

	return ans;
}

int main() {
	double x;
	double formulaAns, taylorAns;
	double error;

	std::cout << std::setprecision(std::numeric_limits<double>::digits10 + 1) << "Enter x number: ";
	std::cin >> x;

	std::cout << "Counting with formula...";
	formulaAns = formulaCount(x);
	std::cout << "\rAnswer with formula: " << formulaAns << "     \n";
	std::cout << "Counting with taylor...";
	taylorAns = taylorCount(x);
	std::cout << "\rAnswer with taylor:  " << taylorAns << "     \n";

	error = std::fabs(taylorAns - formulaAns) / std::fabs(formulaAns);
	std::cout << "Total error: " << error;
}