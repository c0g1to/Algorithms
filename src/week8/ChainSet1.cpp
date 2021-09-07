#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <cmath>
#include "edx-io.hpp"

using namespace std;


class HashCode {
private:
    const int C;
    const int size;

public:
    HashCode(int C, int size) : C(C), size(size) {}

    long long operator()(long long key) const {
        return abs(C * key % size);
    }
};


class ChainSet {
private:
    vector<list<long long>> table;
    HashCode hashCode;
    inline static list<long long> *current;

public:
    explicit ChainSet(int size, int hash_const = 1) : table(size, list<long long>()), hashCode(hash_const, size) {}

    void insert(long long value) {
        if (*search(value) != value)
            current->push_front(value);
    }

    void remove(long long value) {
        auto search_result = search(value);
        if (*search_result == value)
            current->erase(search_result);
    }

    string check(long long value) {
        return *search(value) == value ? "Y\n" : "N\n";
    }

private:
    list<long long>::iterator search(long long value) {
        current = &(*this)[value];
        return find(current->begin(), current->end(), value);
    }

    list<long long> &operator[](long long value) {
        return table[hashCode(value)];
    }
};


int main() {
    edx_io io;
    int N;
    long long value;
    char operation;
    io >> N;
    ChainSet c_set(N / 2 + 1);

    for (int i = 1; i <= N; ++i) {
        io >> operation >> value;
        switch (operation) {
            case 'A':
                c_set.insert(value);
                break;

            case 'D':
                c_set.remove(value);
                break;

            case '?':
                io << c_set.check(value);
                break;
        }
    }

    return 0;
}