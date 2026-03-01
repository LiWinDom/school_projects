#include <iostream>
#include <algorithm>
#include <vector>
#include <random>

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dist(-2147483648, 2147483647);
const double fi = 1.247;

std::vector<long> generateVector(const long& size) {
    std::vector<long> array(size, 0);

    for (int i = 0; i < size; ++i) {
        array[i] = dist(gen);
    }

    return array;
}

bool check(const std::vector<long>& array) {
    for (int i = 1; i < array.size(); ++i) {
        if (array[i] < array[i - 1]) return false;
    }

    return true;
}

std::pair<long, long> bubbleSort(std::vector<long>& array, const bool& mode = false) {
    std::pair<long, long> count = std::pair<long, long>(0, 0);

    for (int i = 0; i < array.size(); ++i) {
        bool swap = false;

        for (int j = 1; j < array.size() - i; ++j) {
            if (array[j] < array[j - 1]) {
                std::swap(array[j], array[j - 1]);
                swap = true;

                count.first += 4;
                if (count.first > 1000000000) return std::pair<long, long>(-1, -1);
            }

            count.second += 2; ++count.first;
            if (count.first > 1000000000 || count.second > 1000000000) return std::pair<long, long>(-1, -1);
        }

        count.second += 2; count.first += 2;
        if (count.first > 1000000000 || count.second > 1000000000) return std::pair<long, long>(-1, -1);

        if (!swap) break;
    }

    ++count.first;

    return count;
}

long long binarySearch(const std::vector<long>& array, const long long& item, const long long& low, const long long& high, std::pair<long, long>& count) {
    ++count.second;

    if (high <= low) {
        ++count.second;

        if (item > array[low]) {
            return low + 1;
        }
        return low;
    }

    ++count.first; ++count.second;

    int mid = (low + high) / 2;

    if (item == array[mid]) {
        return mid + 1;
    }

    ++count.second;

    if (item > array[mid]) {
        return binarySearch(array, item, mid + 1, high, count);
    }
    return binarySearch(array, item, low, mid, count);
}

std::pair<long, long> insertionsSort(std::vector<long>& array, const bool& mode = false) {
    std::pair<long, long> count = std::pair<long, long>(1, 1);

    for (long long i = 1; i < array.size(); ++i) {
        long long loc = binarySearch(array, array[i], 0, i, count);
        if (count.first > 1000000000 || count.second > 1000000000) return std::pair<long, long>(-1, -1);

        for (int j = loc; j < i; ++j) {
            std::swap(array[i], array[j]);
            count.first += 4; ++count.second;
        }

        ++count.first; ++count.second;
        if (count.first > 1000000000 || count.second > 1000000000) return std::pair<long, long>(-1, -1);
    }

    return count;
}

std::pair<long, long> mergeSort(std::vector<long>& array, const int& l, const int& r, const bool& mode = false) {
    std::pair<long, long> count = std::pair<long, long>(0, 1), fir, sec;

    if (l + 1 >= r) {
        return count;
    }

    long mid = (r + l) / 2;

    fir = mergeSort(array, l, mid, mode);
    if (fir.first == -1) return std::pair<long, long>(-1, -1);
    sec = mergeSort(array, mid, r, mode);
    if (fir.first == -1) return std::pair<long, long>(-1, -1);
    count.first += fir.first + sec.first + 4;
    count.second += fir.second + sec.second + 2;

    std::vector<long> buf;
    int l_cur = l, r_cur = mid;
    for (long i = l; i < r; i++) {
        if (l_cur < mid && r_cur < r) {
            if (array[l_cur] < array[r_cur]) {
                buf.push_back(array[l_cur]);
                l_cur++;
            }
            else {
                buf.push_back(array[r_cur]);
                r_cur++;
            }
        }
        else if (l_cur < mid) {
            buf.push_back(array[l_cur]);
            l_cur++;
        }
        else {
            buf.push_back(array[r_cur]);
            r_cur++;
        }

        count.first += 3;
        count.second += 3;
    }
    for (int i = l; i < r; ++i) {
        array[i] = buf[i - l];

        ++count.second;
        ++count.first;
    }

    return count;
}

std::pair<long, long> quickSort(std::vector<long>& array, const int& l, const int& r, const bool& mode = false) {
    std::pair<long, long> count = std::pair<long, long>(0, 1), fir, sec;

    if (l + 1 < r) {
        count.first += 3;

        int pivot = array[r - 1], i = l, j = r - 1, mid;
        while (true) {
            count.first += 4;
            count.second += 12;
            if (count.first > 1000000000) return std::pair<long, long>(-1, -1);

            if (array[i] == pivot && array[j] == pivot) {
                count.first += 2;
                if (count.first > 1000000000 || count.second > 1000000000) return std::pair<long, long>(-1, -1);

                ++i; ++j;
                continue;
            }
            while (array[i] < pivot && i < r) {
                ++i;

                ++count.first; count.second+= 3;
                if (count.first > 1000000000 || count.second > 1000000000) return std::pair<long, long>(-1, -1);
            }
            while (array[j] > pivot && j >= 0) {
                --j;

                ++count.first; count.second += 3;
                if (count.first > 1000000000 || count.second > 1000000000) return std::pair<long, long>(-1, -1);
            }
            if (i >= j) {
                ++count.first;
                if (count.first > 1000000000) return std::pair<long, long>(-1, -1);

                mid = j;
                break;
            }
            std::swap(array[i], array[j]);

            count.first += 3;
            if (count.first > 1000000000) return std::pair<long, long>(-1, -1);
        }

        fir = quickSort(array, l, mid, mode);
        sec = quickSort(array, mid + 1, r, mode);
        count.first += fir.first + sec.first;
        count.second += fir.second + sec.second + 1;
    }

    return count;
}

std::pair<long, long> combSort(std::vector<long>& array, const bool& mode = false) {
    std::pair<long, long> count = std::pair<long, long>(1, 1);
    int step = array.size() / fi;

    while (true) {
        bool swap = true;
        if (step < 1) {
            swap = false;
            step = 1;
            count.first += 2;
            if (count.first > 1000000000) return std::pair<long, long>(-1, -1);
        }

        count.second += 4;  count.first += 2;
        if (count.first > 1000000000 || count.second > 1000000000) return std::pair<long, long>(-1, -1);

        for (int i = 0; i < array.size(); ++i) {
            count.second += 2;
            if (count.second > 1000000000) return std::pair<long, long>(-1, -1);

            if (i + step >= array.size()) break;

            ++count.second;
            if (count.second > 1000000000) return std::pair<long, long>(-1, -1);

            if (array[i] > array[i + step]) {
                std::swap(array[i], array[i + step]);
                swap = true;

                count.first += 4;
                if (count.first > 1000000000) return std::pair<long, long>(-1, -1);
            }
        }

        if (!swap) break;
        step /= fi;
    }

    return count;
}

std::pair<long, long> shellSort(std::vector<long>& array, const bool& mode = false) {
    std::pair<long, long> count = std::pair<long, long>(1, 1);
    int step = array.size() / fi;

    while (true) {
        bool swap = true;
        if (step < 1) {
            swap = false;
            step = 1;
            count.first += 2;
            if (count.first > 1000000000) return std::pair<long, long>(-1, -1);
        }

        count.first += 2; count.second += 2;
        if (count.first > 1000000000 || count.second > 1000000000) return std::pair<long, long>(-1, -1);

        for (int i = step; i < array.size(); ++i) {
            count.first += 2; ++count.second;
            if (count.first > 1000000000 || count.second > 1000000000) return std::pair<long, long>(-1, -1);

            for (int j = i - step; j >= 0; j -= step) {
                ++count.first; ++count.second;
                if (count.first > 1000000000 || count.second > 1000000000) return std::pair<long, long>(-1, -1);

                if (array[j] > array[j + step]) {
                    std::swap(array[j], array[j + step]);
                    swap = true;

                    count.first += 4;
                    if (count.first > 1000000000) return std::pair<long, long>(-1, -1);
                }
                else {
                    break;
                }
            }
        }
        

        if (!swap) break;
        step /= fi;
    }

    return count;
}

void compareSorts(const long& size) {
    std::cout << "Generating array...";
    std::vector<long> array = generateVector(size);
    std::vector<long> bubbleArray = array, insertionsArray = array, mergeArray = array, quickArray = array, combArray = array, shellArray = array;
    std::pair<long, long> bubbleResult, insertionsResult, mergeResult, quickResult, combResult, shellResult;
    std::cout << " DONE!\n";

    /*std::cout << '\n';
    std::cout << "Bubble sort assigments: ";
    bubbleResult = bubbleSort(bubbleArray, true);
    if (bubbleResult.first == -1) {
        std::cout << "time break!\n";
        std::cout << "Bubble sort comparations: time break!\n";
    }
    else {
        std::cout << bubbleResult.first << '\n';
        std::cout << "Bubble sort comparations: ";
        std::cout << bubbleResult.second << '\n';
        std::cout << "[CHECK] Bubble sort - ";
        if (check(bubbleArray)) std::cout << "OK!\n";
        else std::cout << "something went wrong...\n";
    }

    std::cout << '\n';
    std::cout << "Insertions sort assigments: ";
    insertionsResult = insertionsSort(insertionsArray, true);
    if(insertionsResult.first == -1) {
        std::cout << "time break!\n";
        std::cout << "Insertions sort comparations: time break!\n";
    }
    else {
        std::cout << insertionsResult.first << '\n';
        std::cout << "Insertions sort comparations: ";
        std::cout << insertionsResult.second << '\n';
        std::cout << "[CHECK] Insertions sort - ";
        if (check(insertionsArray)) std::cout << "OK!\n";
        else std::cout << "something went wrong...\n";
    }

    std::cout << '\n';
    std::cout << "Merge sort assigments: ";
    mergeResult = mergeSort(mergeArray, 0, mergeArray.size(), true);
    if (mergeResult.first == -1) {
        std::cout << "time break!\n";
        std::cout << "Merge sort comparations: time break!\n";
    }
    else {
        std::cout << mergeResult.first << '\n';
        std::cout << "Merge sort comparations: ";
        std::cout << mergeResult.second << '\n';
        std::cout << "[CHECK] Merge sort - ";
        if (check(mergeArray)) std::cout << "OK!\n";
        else std::cout << "something went wrong...\n";
    }*/

    std::cout << '\n';
    std::cout << "Quick sort assigments: ";
    quickResult = quickSort(quickArray, 0, quickArray.size(), true);
    if (quickResult.first == -1) {
        std::cout << "time break!\n";
        std::cout << "Quick sort comparations: time break!\n";
    }
    else {
        std::cout << quickResult.first << '\n';
        std::cout << "Quick sort comparations: ";
        std::cout << quickResult.second << '\n';
        std::cout << "[CHECK] Quick sort - ";
        if (check(quickArray)) std::cout << "OK!\n";
        else std::cout << "something went wrong...\n";
    }

    /*std::cout << '\n';
    std::cout << "Comb sort assigments: ";
    combResult = combSort(combArray, true);
    if (combResult.first == -1) {
        std::cout << "time break!\n";
        std::cout << "Comb sort comparations: time break!\n";
    }
    else {
        std::cout << combResult.first << '\n';
        std::cout << "Comb sort comparations: ";
        std::cout << combResult.second << '\n';
        std::cout << "[CHECK] Comb sort - ";
        if (check(combArray)) std::cout << "OK!\n";
        else std::cout << "something went wrong...\n";
    }

    std::cout << '\n';
    std::cout << "Shell sort assigments: ";
    shellResult = shellSort(shellArray, true);
    if (shellResult.first == -1) {
        std::cout << "time break!\n";
        std::cout << "Shell sort comparations: time break!\n";
    }
    else {
        std::cout << shellResult.first << '\n';
        std::cout << "Shell sort comparations: ";
        std::cout << shellResult.second << '\n';
        std::cout << "[CHECK] Shell sort - ";
        if (check(shellArray)) std::cout << "OK!\n";
        else std::cout << "something went wrong...\n";
    }*/

    return;
}

int main() {
    while (true) {
        int n;
        std::vector<long> array;
        std::cout << "Enter length of random array (0 to exit): ";
        std::cin >> n;
        if (n < 1) {
            break;
        }
        //array = generateVector(n);

        //bubbleSort(array);
        //insertionsSort(array);
        //mergeSort(array, 0, array.size());
        //quickSort(array, 0, array.size());
        //combSort(array);
        //shellSort(array);

        compareSorts(n);
        std::cout << "\n\n";
    }
    std::cout << "Bye!";

    return 0;
}