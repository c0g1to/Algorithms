#include <iostream>
#include "edx-io.hpp"

using namespace std;

class queue {
private:
    int* data = nullptr;
    int first_el_index;
    int last_el_index;

public:
    explicit queue(int size = 10) {
        data = new int[size];
        this->first_el_index = 0;
        this->last_el_index = -1;
    }

    void push(int element) {
        data[++last_el_index] = element;
    }

    int pop() {
        int temp = data[first_el_index];
        data[first_el_index++] = 0;
        return temp;
    }

    ~queue() {
        delete[] data;
        data = nullptr;
    }
};

int main() {
    edx_io io = edx_io();
    int n, el;
    char op;
    io >> n;
    queue storage = queue(n);

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