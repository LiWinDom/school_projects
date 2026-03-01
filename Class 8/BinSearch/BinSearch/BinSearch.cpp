#include <iostream>

int main() {
    uint64_t num;

    while (std::cin >> num) {
        if (num == 0) {
            std::cout << 0 << '\n';
            continue;
        }
        if (num == 1) {
            std::cout << 1 << '\n';
            continue;
        }
        uint64_t l = 1, r = num;
        while (r - l > 1) {
            uint64_t mid = l + (r - l) / 2;
            if (mid <= num / mid) {
                l = mid;
            }
            else {
                r = mid;
            }
        }
        std::cout << l << '\n';
    }
}
