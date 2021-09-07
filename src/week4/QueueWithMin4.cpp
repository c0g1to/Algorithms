#include <iostream>
#include <set>
#include "../mooc/edx-io.hpp"

using namespace std;

class queue {
private:
    int *data = nullptr;
    multiset<int> sorted_data;
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
        sorted_data.insert(element);
    }

    int pop() {
        int temp = data[first_el_index];
        data[first_el_index++] = 0;
        sorted_data.erase(sorted_data.find(temp));
        return temp;
    }

    int min() const {
        return *sorted_data.begin();
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
        switch (op) {
            case '+':
                io >> el;
                storage.push(el);
                break;

            case '-':
                storage.pop();
                break;

            case '?':
                io << storage.min() << '\n';
                break;
        }
    }

    return 0;
}