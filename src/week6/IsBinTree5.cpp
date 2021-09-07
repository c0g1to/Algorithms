#include "edx-io.hpp"
#include <climits>

using namespace std;
// 91% correct

struct Node {
    int value;
    int parent_index;
    bool is_right_child;
};

bool is_correct(int value, int next_relative, bool next_child_side, const Node* bin_arr) {
    if (next_relative == 0)
        return true;
    if (next_child_side && bin_arr[next_relative].value < value
        || !next_child_side && bin_arr[next_relative].value > value) {
        return is_correct(value, bin_arr[next_relative].parent_index, bin_arr[next_relative].is_right_child, bin_arr);
    } else {
        return false;
    }
}

int main() {
    edx_io io = edx_io();
    string result = "YES\n";
    int N, LR[2];
    io >> N;
    Node *bin_arr = new Node[N + 1];

    bin_arr[1].parent_index = 0;
    bin_arr[1].is_right_child = true;
    bin_arr[0].value = INT_MIN;

    for (int line = 1; line <= N; ++line) {
        io >> bin_arr[line].value >> LR[0] >> LR[1];
        if (is_correct(bin_arr[line].value, bin_arr[line].parent_index, bin_arr[line].is_right_child, bin_arr)) {
            for (int i = 0; i < 2; ++i) {
                bin_arr[LR[i]].parent_index = line;
                bin_arr[LR[i]].is_right_child = i;
            }
        } else
            result = "NO\n";
    }

    io << result;
    delete[] bin_arr;
    bin_arr = nullptr;
    return 0;
}