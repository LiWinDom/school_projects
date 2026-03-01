#include <iostream>

struct Stack {
    int data[10000];
    int sz = 0;

    void push(int n) {
        if (sz > 9999) {
            std::cout << "error \n";
            return;
        }
        data[sz++] = n;
        std::cout << "ok \n";

        return;
    }

    void pop() {
        if (sz < 1) {
            std::cout << "error \n";
            return;
        }
        std::cout << data[--sz] << '\n';
        return;
    }

    void back() {
        if (sz < 1) {
            std::cout << "error \n";
            return;
        }
        std::cout << data[sz - 1] << '\n';
        return;
    }

    void size() {
        std::cout << sz << '\n';
        return;
    }

    void clear() {
        sz = 0;
        std::cout << "ok \n";

        return;
    }
};

struct Queue {
    int data[10000];
    int sz = 0, head = 0, tail = 0;

    void push(int n) {
        if (sz > 9999) {
            std::cout << "error \n";
            return;
        }
        if (head > 9999) {
            head = 0;
        }
        data[head++] = n;
        ++sz;
        std::cout << "ok \n";

        return;
    }

    void pop() {
        if (sz < 1) {
            std::cout << "error \n";
            return;
        }
        if (tail > 9999) {
            tail = 0;
        }
        std::cout << data[tail++] << '\n';
        --sz;

        return;
    }

    void front() {
        if (sz < 1) {
            std::cout << "error \n";
            return;
        }
        std::cout << data[tail] << '\n';
        return;
    }

    void size() {
        std::cout << sz << '\n';
        return;
    }

    void clear() {
        sz = 0, head = 0, tail = 0;
        std::cout << "ok \n";

        return;
    }
};

struct Deque {
    int data[10000];
    int sz = 0, head = 0, tail = 9999;

    void push_front(int n) {
        if (sz > 9999) {
            std::cout << "error \n";
            return;
        }
        if (head > 9999) {
            head = 0;
        }
        data[head++] = n;
        ++sz;
        std::cout << "ok \n";

        return;
    }

    void push_back(int n) {
        if (sz > 9999) {
            std::cout << "error \n";
            return;
        }
        if (tail < 0) {
            tail = 9999;
        }
        data[tail--] = n;
        ++sz;
        std::cout << "ok \n";

        return;
    }

    void pop_front() {
        if (sz < 1) {
            std::cout << "error \n";
            return;
        }
        if (head < 1) {
            head = 10000;
        }
        std::cout << data[--head] << '\n';
        --sz;

        return;
    }

    void pop_back() {
        if (sz < 1) {
            std::cout << "error \n";
            return;
        }
        if (tail > 9998) {
            tail = -1;
        }
        std::cout << data[++tail] << '\n';
        --sz;

        return;
    }

    void front() {
        if (sz < 1) {
            std::cout << "error \n";
            return;
        }
        if (head < 1) {
            std::cout << data[9999] << '\n';
        }
        else {
            std::cout << data[head - 1] << '\n';
        }
        return;
    }

    void back() {
        if (sz < 1) {
            std::cout << "error \n";
            return;
        }
        if (tail > 9998) {
            std::cout << data[0] << '\n';
        }
        else {
            std::cout << data[tail + 1] << '\n';
        }
        return;
    }

    void size() {
        std::cout << sz << '\n';
        return;
    }

    void clear() {
        sz = 0, head = 0, tail = 9999;
        std::cout << "ok \n";

        return;
    }
};

void stack() {
    Stack stack;

    while (true) {
        std::string command;

        std::cin >> command;
        if (command == "push") {
            int n;

            std::cin >> n;
            stack.push(n);
            std::cout << '\n';
        }
        else if (command == "pop") {
            stack.pop();
            std::cout << '\n';
        }
        else if (command == "back") {
            stack.back();
            std::cout << '\n';
        }
        else if (command == "size") {
            stack.size();
            std::cout << '\n';
        }
        else if (command == "clear") {
            stack.clear();
            std::cout << '\n';
        }
        else if (command == "exit") {
            break;
        }
        else {
            std::cout << "invalid command \n\n";
        }
    }
    std::cout << "bye";
}

void queue() {
    Queue queue;

    while (true) {
        std::string command;

        std::cin >> command;
        if (command == "push") {
            int n;

            std::cin >> n;
            queue.push(n);
            std::cout << '\n';
        }
        else if (command == "pop") {
            queue.pop();
            std::cout << '\n';
        }
        else if (command == "front") {
            queue.front();
            std::cout << '\n';
        }
        else if (command == "size") {
            queue.size();
            std::cout << '\n';
        }
        else if (command == "clear") {
            queue.clear();
            std::cout << '\n';
        }
        else if (command == "exit") {
            break;
        }
        else {
            std::cout << "invalid command \n\n";
        }
    }
    std::cout << "bye";
}

void deque() {
    Deque deque;

    while (true) {
        std::string command;

        std::cin >> command;
        if (command == "push_front") {
            int n;

            std::cin >> n;
            deque.push_front(n);
            std::cout << '\n';
        }
        else if (command == "push_back") {
            int n;

            std::cin >> n;
            deque.push_back(n);
            std::cout << '\n';
        }
        else if (command == "pop_front") {
            deque.pop_front();
            std::cout << '\n';
        }
        else if (command == "pop_back") {
            deque.pop_back();
            std::cout << '\n';
        }
        else if (command == "front") {
            deque.front();
            std::cout << '\n';
        }
        else if (command == "back") {
            deque.back();
            std::cout << '\n';
        }
        else if (command == "size") {
            deque.size();
            std::cout << '\n';
        }
        else if (command == "clear") {
            deque.clear();
            std::cout << '\n';
        }
        else if (command == "exit") {
            break;
        }
        else {
            std::cout << "invalid command \n\n";
        }
    }
    std::cout << "bye";
}

int main() {
    //stack();
    //queue();
    deque();

    return 0;
}