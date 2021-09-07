#include <iostream>
#include "edx-io.hpp"

using namespace std;

class stack {
private:
    int* data = nullptr;
    int last_el_index = -1;

public:
    explicit stack(int size = 10) {
        data = new int[size];
    }

    void push(int element) {
        data[++last_el_index] = element;
    }

    int pop() {
        int temp = data[last_el_index];
        data[last_el_index--] = 0;
        return temp;
    }

    ~stack() {
        delete[] data;
        data = nullptr;
    }
};

int main() {
    edx_io io = edx_io();
    int n, el;
    char op;
    io >> n;
    stack storage = stack(n);

    for (int i = 0; i < n; i++) {
        io >> op;
        if (op == '+') {
            io >> el;
            storage.push(el);
        } else {
            io << storage.pop() << '\n';
        }
    }

    return 0;
}