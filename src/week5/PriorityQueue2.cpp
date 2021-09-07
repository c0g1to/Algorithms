#include <iostream>
#include <unordered_map>
#include <vector>
#include <climits>
#include "../mooc/edx-io.hpp"

using namespace std;

class dmap {
private:
    unordered_map<int, int> first_to_second;
    unordered_map<int, int> second_to_first;

public:
    void set(int first, int second) {
        if (first_to_second.count(first) == 0 && second_to_first.count(second) == 0) {
            first_to_second[first] = second;
            second_to_first[second] = first;
        }
    }

    int get_first(int second) {
        return second_to_first[second];
    }

    int get_second(int first) {
        return first_to_second[first];
    }

    void erase_by_first(int first) {
        int second = first_to_second[first];
        first_to_second.erase(first);
        second_to_first.erase(second);
    }

    void erase_by_second(int second) {
        int first = second_to_first[second];
        second_to_first.erase(second);
        first_to_second.erase(first);
    }

    void swap_by_first(int first1, int first2) {
        int second1 = first_to_second[first1];
        int second2 = first_to_second[first2];
        first_to_second[first1] = second2;
        first_to_second[first2] = second1;
        second_to_first[second1] = first2;
        second_to_first[second2] = first1;
    }

    void swap_by_second(int second1, int second2) {
        int first1 = second_to_first[second1];
        int first2 = second_to_first[second2];
        second_to_first[second1] = first2;
        second_to_first[second2] = first1;
        first_to_second[first1] = second2;
        first_to_second[first2] = second1;
    }

    explicit operator string() {
        string output;
        for (auto &it : first_to_second) {
            output += '(' + to_string(it.first) + ':' + to_string(it.second) + ") ";
        }
        return output;
    }
};

class priority_queue {          //DESCENDING ORDER
private:
    vector<int> values;
    dmap order_to_index;

public:
    explicit priority_queue(int size) {
        values.emplace_back(INT_MIN);
        order_to_index.set(0, 0);
    }

    void add(int order, int value) {
        values.emplace_back(value);
        order_to_index.set(order, last_index());
        pull_up(last_index());
    }

    void replace(int order, int value) {
        int index = order_to_index.get_second(order);
        if (value < values[index]) {
            values[index] = value;
            pull_up(index);
        } else {
            values[index] = value;
            pull_down(index);
        }
    }

    string remove() {
        if (last_index() == 0) {
            return "*";
        }
        string min_value = to_string(values[1]);
        full_swap(1, last_index());
        full_pop_back();
        pull_down(1);
        return min_value;
    }

//    void print(int line) {
//        cout << "LINE " << line << endl;
//        cout << "Is heap? " << is_heap() << endl;
//        cout << "values: ";
//        for (int value : values) {
//            cout << value << ' ';
//        }
//        cout << endl << "order_to_index: " + string(order_to_index) << endl << endl;
//    }

private:
    int last_index() {
        return values.size() - 1;
    }

    void full_swap(int index1, int index2) {
        swap(values[index1], values[index2]);
        order_to_index.swap_by_second(index1, index2);
    }

    void full_pop_back() {
        order_to_index.erase_by_second(last_index());
        values.pop_back();
    }

    void pull_up(int index) {
        while (values[index] < values[index / 2]) {
            full_swap(index, index / 2);
            index = index / 2;
        }
    }

    void pull_down(int index) {
        while (2 * index <= last_index() &&
               values[index] > values[2 * index] ||
               2 * index + 1 <= last_index() &&
               values[index] > values[2 * index + 1]) {
            if (2 * index + 1 > last_index() || values[2 * index] < values[2 * index + 1]) {
                full_swap(index, 2 * index);
                index = 2 * index;
            } else {
                full_swap(index, 2 * index + 1);
                index = 2 * index + 1;
            }
        }
    }

//    string is_heap() {
//        for (int i = 0; 2 * i + 1 <= last_index(); i++) {
//            if (values[i] > values[2 * i] || values[i] > values[2 * i + 1]) {
//                return "NOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO";
//            }
//        }
//        if (!(last_index() % 2) && values[last_index() / 2] > values[last_index()]) {
//            return "NOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO";
//        }
//        return "YES";
//    }
};

int main() {
    edx_io io = edx_io();
    int n, x, y;
    char op;
    io >> n;
    priority_queue pqueue = priority_queue(n);

    for (int line = 1; line <= n; ++line) {
        io >> op;
        switch (op) {
            case 'A':
                io >> x;
                pqueue.add(line, x);
                break;

            case 'X':
                io << pqueue.remove() << '\n';
                break;

            case 'D':
                io >> x >> y;
                pqueue.replace(x, y);
                break;
        }
//        pqueue.print(line);
    }

    return 0;
}