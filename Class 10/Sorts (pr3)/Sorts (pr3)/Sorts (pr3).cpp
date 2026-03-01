#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <ctime>
#include <vector>
#include <string>
#include <fstream>
#include <bitset>

int comp(const void* a, const void* b) {
    if (*(double*)a > *(double*)b) return 1;
    else if (*(double*)a < *(double*)b) return -1;
    else return 0;
}

double random() {
    return (double)rand() * rand() * rand() / RAND_MAX / rand();
}

std::vector<double> generateArray(uint64_t elemsNum) {
    std::vector<double> arr(elemsNum, 0);

    for (uint64_t i = 0; i < elemsNum; ++i) {
        arr[i] = random();
    }
    return arr;
}

bool checkSort(const std::vector<double>& arr) {
    for (uint64_t i = 1; i < arr.size(); ++i) {
        if (arr[i - 1] > arr[i]) return false;
    }
    return true;
}

void qsort(std::vector<double>& arr, const uint64_t& start, const uint64_t& end) {
    if (start + 1 >= end) return;
    double pivot = arr[start];

    // Partition
    uint64_t l = start - 1;
    uint64_t r = end;
    while (true) {
        do {
            ++l;
        } while (arr[l] < pivot);
        do {
            --r;
        } while (arr[r] > pivot);
        if (l >= r) {
            break;
        }
        std::swap(arr[l], arr[r]);
    }
    qsort(arr, start, r + 1);
    qsort(arr, r + 1, end);

    return;
}

uint8_t getByte(double num, const uint8_t& byte) {
    uint64_t* adr = (uint64_t*)&num;
    return (*adr >> (byte * 8)) & 255;
}

void sortByte(std::vector<double>& arr, const uint8_t& byte) {
    uint64_t count[256];
    for (uint16_t i = 0; i < 256; ++i) {
        count[i] = 0;
    }

    std::vector<double> tmp = std::vector<double>(arr.size(), 0);
    for (uint64_t i = 0; i < arr.size(); ++i) {
        ++count[getByte(arr[i], byte)];
    }
    for (uint16_t i = 1; i < 256; ++i) {
        count[i] += count[i - 1];
    }
    for (int64_t i = arr.size() - 1; i >= 0; --i) {
        tmp[--count[getByte(arr[i], byte)]] = arr[i];
    }
    arr = tmp;
    return;
}

void radixSort(std::vector<double>& arr) {
    for (uint8_t i = 0; i < 8; ++i) {
        sortByte(arr, i);
    }
    return;
}

void heapify(std::vector<double>& arr, int n, int i)
{
    uint64_t largest = i;
    uint64_t l = 2 * i + 1;
    uint64_t r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest]) {
        largest = l;
    }

    if (r < n && arr[r] > arr[largest]) {
        largest = r;
    }

    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(std::vector<double>& arr) {
    for (int64_t i = arr.size() / 2 - 1; i >= 0; i--) {
        heapify(arr, arr.size(), i);
    }

    for (int64_t i = arr.size() - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
    return;
}

int main() {
    std::ofstream file;
    file.open("log.txt");
    std::cout << std::fixed;

    for (uint16_t i = 1; i <= 7; ++i) {
        std::cout << "========== Analyze #" << i << " ==========" << std::endl;
        file << "========== Analyze #" << i << " ==========" << std::endl;

        for (uint64_t sz = 10; sz < 100000000; sz *= 10) {
            typedef std::chrono::high_resolution_clock clock;
            typedef std::chrono::duration<float, std::milli> duration;

            std::cout << "Array size: " << sz << std::endl;
            file << "Array size: " << sz << std::endl;

            // Generating array
            std::cout << "Generating array . . . ";
            std::vector<double> arr = generateArray(sz);
            std::cout << "Done!" << std::endl;

            std::vector<double> sort = arr;
            // std::sort
            std::cout << "[std::sort] Sorting array . . . ";
            file << "[std::sort] Sorting array . . . ";
            clock::time_point start = clock::now();
            std::sort(sort.begin(), sort.end());
            duration elapsed = clock::now() - start;
            std::cout << elapsed.count() << "ms" << std::endl;
            file << elapsed.count() << "ms" << std::endl;
            std::cout << "[std::sort] Checking sort . . . ";
            file << "[std::sort] Checking sort . . . ";
            if (checkSort(sort)) {
                std::cout << "OK!" << std::endl;
                file << "OK!" << std::endl;
            }
            else {
                file << "went wrong, closing...";
                file.close();
                std::cout << "went wrong, closing...";
                system("pause");
                return 1;
            }

            sort = arr;
            // std::qsort
            std::cout << "[std::qsort] Sorting array . . . ";
            file << "[std::qsort] Sorting array . . . ";
            start = clock::now();
            std::qsort(&sort[0], sort.size(), sizeof(double), comp);
            elapsed = clock::now() - start;
            std::cout << elapsed.count() << "ms" << std::endl;
            file << elapsed.count() << "ms" << std::endl;
            std::cout << "[std::qsort] Checking sort . . . ";
            file << "[std::qsort] Checking sort . . . ";
            if (checkSort(sort)) {
                std::cout << "OK!" << std::endl;
                file << "OK!" << std::endl;
            }
            else {
                file << "went wrong, closing...";
                file.close();
                std::cout << "went wrong...";
                system("pause");
                return 1;
            }

            sort = arr;
            // My quick sort
            std::cout << "[qsort] Sorting array . . . ";
            file << "[qsort] Sorting array . . . ";
            start = clock::now();
            qsort(sort, 0, sort.size());
            elapsed = clock::now() - start;
            std::cout << elapsed.count() << "ms" << std::endl;
            file << elapsed.count() << "ms" << std::endl;
            std::cout << "[qsort] Checking sort . . . ";
            file << "[qsort] Checking sort . . . ";
            if (checkSort(sort)) {
                std::cout << "OK!" << std::endl;
                file << "OK!" << std::endl;
            }
            else {
                file << "went wrong, closing...";
                file.close();
                std::cout << "went wrong...";
                system("pause");
                return 1;
            }

            sort = arr;
            // Radix sort
            std::cout << "[radix] Sorting array . . . ";
            file << "[radix] Sorting array . . . ";
            start = clock::now();
            radixSort(sort);
            elapsed = clock::now() - start;
            std::cout << elapsed.count() << "ms" << std::endl;
            file << elapsed.count() << "ms" << std::endl;
            std::cout << "[radix] Checking sort . . . ";
            file << "[radix] Checking sort . . . ";
            if (checkSort(sort)) {
                std::cout << "OK!" << std::endl;
                file << "OK!" << std::endl;
            }
            else {
                file << "went wrong, closing...";
                file.close();
                std::cout << "went wrong...";
                system("pause");
                return 1;
            }

            sort = arr;
            // Heap sort
            std::cout << "[heap] Sorting array . . . ";
            file << "[heap] Sorting array . . . ";
            start = clock::now();
            heapSort(sort);
            elapsed = clock::now() - start;
            std::cout << elapsed.count() << "ms" << std::endl;
            file << elapsed.count() << "ms" << std::endl;
            std::cout << "[heap] Checking sort . . . ";
            file << "[heap] Checking sort . . . ";
            if (checkSort(sort)) {
                std::cout << "OK!" << std::endl;
                file << "OK!" << std::endl;
            }
            else {
                file << "went wrong, closing...";
                file.close();
                std::cout << "went wrong...";
                system("pause");
                return 1;
            }

            std::cout << std::endl;
            file << std::endl;
        }
        std::cout << std::endl;
        file << std::endl;
    }
    file.close();
    std::cout << "All data has been written to the file" << std::endl;
    system("pause");

    return 0;
}
