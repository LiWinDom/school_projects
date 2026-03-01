#include <iostream>
#include <algorithm>
#include <vector>

struct Node {
    int data;
    Node* left = nullptr;
    Node* right = nullptr;
};

void insert(Node*& t, int key) {
    if (t == nullptr) {
        t = new Node;
        t->data = key;
        return;
    }
    if (key > t->data) {
        insert(t->right, key);
    }
    else if (key < t->data) {
        insert(t->left, key);
    }
    else {
        throw "H";
    }
    return;
}

void insertArray(Node*& t, std::vector<int> keys, int start, int end) {
    if (start >= end) return;
    insert(t, keys[(start + end) / 2]);
    insertArray(t, keys, start, (start + end) / 2);
    insertArray(t, keys, (start + end) / 2 + 1, end);
    return;
}

int countHeight(Node* t) {
    if (t == nullptr) return 0;
    return std::max(countHeight(t->left), countHeight(t->right)) + 1;
}

int main() {
    std::vector<int> keys(0, 0);
    int n = 0;
    std::cin >> n;

    Node* tree = nullptr;

    for (int i = 0; i < n; ++i) {
        int k;
        std::cin >> k;
        keys.push_back(k);
    }

    std::sort(keys.begin(), keys.end());

    insertArray(tree, keys, 0, n);

    std::cout << countHeight(tree);

    return 0;
}
