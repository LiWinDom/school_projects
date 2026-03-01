#include <iostream>
#include <vector>

class CustomRandom {
private:
	uint64_t seeds[3];
	uint64_t coefficients[4];
	uint64_t past[3];
public:
	CustomRandom(const uint64_t& a, const uint64_t& b, const uint64_t& c, const uint64_t& d) {
		coefficients[0] = a;
		coefficients[1] = b;
		coefficients[2] = c;
		coefficients[3] = d;
	}

	void Reset() {
		past[0] = seeds[0];
		past[1] = seeds[1];
		past[2] = seeds[2];

		return;
	}

	void SetSeed(const uint64_t& x0, const uint64_t& x1, const uint64_t& x2) {
		seeds[0] = x0;
		seeds[1] = x1;
		seeds[2] = x2;
		Reset();

		return;
	}

	void ReInit(const uint64_t& a, const uint64_t& b, const uint64_t& c, const uint64_t& d) {
		coefficients[0] = a;
		coefficients[1] = b;
		coefficients[2] = c;
		coefficients[3] = d;

		return;
	}

	uint64_t Next(uint64_t cycles = 1) {
		for (uint64_t i = 0; i < cycles; ++i) {
			uint64_t rand_number = (coefficients[0] * past[2] + coefficients[1] * past[1] + coefficients[2] * past[0]) % coefficients[3];
			past[0] = past[1];
			past[1] = past[2];
			past[2] = rand_number;
		}

		return past[2];
	}
};

void CountCycleSize(const uint64_t& a, const uint64_t& b, const uint64_t& c, const uint64_t& d,
					const uint64_t& x0, const uint64_t x1, const uint64_t x2) {
	uint64_t cycle_size = 0, ahilleses[3] = {x0, x1, x2}, thurtles[3] = {x0, x1, x2};


	std::cout << "\n---COUNTING SYCLES SIZES---\n";
	CustomRandom ahilles(a, b, c, d), thurtle(a, b, c, d);

	std::cout << "Counting cycle size...\n";
	ahilles.SetSeed(x0, x1, x2), thurtle.SetSeed(x0, x1, x2);

	std::cout << "Searching definetly in cycle number...";
	do {
		thurtles[0] = thurtles[1], thurtles[1] = thurtles[2], thurtles[2] = thurtle.Next();
		ahilleses[0] = ahilleses[2], ahilleses[1] = ahilles.Next(), ahilleses[2] = ahilles.Next();
	} while (ahilleses[0] != thurtles[0] || ahilleses[1] != thurtles[1] || ahilleses[2] != thurtles[2]);
	std::cout << " OK! It's " << ahilleses[0] << ", " << ahilleses[1] << " and " << ahilleses[2] << '\n';

	std::cout << "Counting cycle size...";
	do {
		ahilleses[0] = ahilleses[1], ahilleses[1] = ahilleses[2], ahilleses[2] = ahilles.Next();
		++cycle_size;
	} while (ahilleses[0] != thurtles[0] || ahilleses[1] != thurtles[1] || ahilleses[2] != thurtles[2]);
	std::cout << " OK! The cycle size is " << cycle_size << '\n';

	std::cout << "Counting precycle size...\n";

	return;
}

void CountDeviation(const uint64_t& a, const uint64_t& b, const uint64_t& c, const uint64_t& d,
	const uint64_t& x0, const uint64_t x1, const uint64_t x2) {
	double random_numbers[400], e = 0;
	uint64_t sum = 0;
	int range[20] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	std::cout << "\n---DEVIATION TEST---\n";
	CustomRandom Random(a, b, c, d);
	Random.SetSeed(x0, x1, x2);

	++range[x0 / d * 20], ++range[x1 / d * 20], ++range[x2 / d * 20];

	std::cout << "Generating 400 numbers...";
	for (int i = 3; i < 400; ++i) {
		double next_num = Random.Next();
		random_numbers[i] = next_num / d;

		int temp = random_numbers[i] * 20;
		++range[temp];
	}
	std::cout << " OK!\n";

	std::cout << "Counting deviation...";
	for (int i = 0; i < 20; ++i) {
		sum += (range[i] - 20) * (range[i] - 20);
	}
	e = sum / 400.0;
	e = std::sqrt(e);
	std::cout << " OK!\n";
	std::cout << "e = " << e << '\n';

	return;
}

void TestRandom(const uint64_t& a, const uint64_t& b, const uint64_t& c, const uint64_t& d,
	const uint64_t& x0, const uint64_t x1, const uint64_t x2) {
	std::cout << "Testing random (a = " << a << ", b = " << b << ", c = " << c << ", d = " << d << "; seed: " << x0 << ", " << x1 << ", " << x2 << '\n';

	CountCycleSize(a, b, c, d, x0, x1, x2);
	CountDeviation(a, b, c, d, x0, x1, x2);

	return;
}

int main() {
	uint64_t a, b, c, d, x0, x1, x2;

	std::cin >> a >> b >> c >> d >> x0 >> x1 >> x2;
	TestRandom(a, b, c, d, x0 % d, x1 % d, x2 % d);

	return 0;
}

//xi = (axi-1 + bxi-2 + cxi-3) % d
//a, b, c, d, x0, x1, x2

/*z
1) 400 чисел (включая x0)
2) Нормальзация xi = xi / d
3) Разбиваем 0-1 на 20 равных отрезков, считаем числа
4) Квадратичное отклонение
	sqrt()
*/