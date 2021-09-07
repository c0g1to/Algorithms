#include <iostream>
#include <map>
#include "edx-io.hpp"
//#include "../mooc/edx-io.hpp"

//doesn't work

using namespace std;

class stack {
private:
    char *data = nullptr;
    int last_el_index;

public:
    explicit stack(int size = 10) {
        data = new char[size];
        this->last_el_index = -1;
    }

    void push(int element) {
        data[++last_el_index] = element;
    }

    char pop() {
        char temp = data[last_el_index];
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
    int n;
    string bracket_sequence;
    const string OPEN_BRACKETS = "([";
    map<char, char> close_open = {{')', '('},
                                  {']', '['}};
    io >> n;

    for (int i = 0; i < n; i++) {
        io >> bracket_sequence;
        stack storage = stack(bracket_sequence.size());
        bool is_correct = true;
        for (char bracket : bracket_sequence) {
            if (OPEN_BRACKETS.find(bracket) != string::npos) {
                storage.push(bracket);
            } else {
                if (close_open[bracket] != storage.pop()) {
                    is_correct = false;
                    break;
                }
            }
        }

        if (is_correct) {
            io << "YES\n";
        } else {
            io << "NO\n";
        }
    }

    return 0;
}