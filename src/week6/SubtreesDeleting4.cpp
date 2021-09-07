#include "edx-io.hpp"
#include <vector>
#include <iostream>

using namespace std;

struct noodle {
    int father_i, value, left_i, right_i, sub_size;
};

int count_sub_size(vector<noodle> &nudes, int index) {
    noodle &nude = nudes[index];
    nude.sub_size =
            (nude.left_i == 0 ? 0 : count_sub_size(nudes, nude.left_i)) +
            (nude.right_i == 0 ? 0 : count_sub_size(nudes, nude.right_i)) + 1;
    return nude.sub_size;
}

int main() {
    edx_io io = edx_io();
    int N, M, bye_value;
    io >> N;
    vector<noodle> nudes(N);

    // stage 1: Array filling
    nudes[0].father_i = -1;
    for (int i = 0; i < N; ++i) {
        io >> nudes[i].value >> nudes[i].left_i >> nudes[i].right_i;

        if (nudes[i].left_i != 0) {
            nudes[i].left_i--;
            nudes[nudes[i].left_i].father_i = i;
        }
        if (nudes[i].right_i != 0) {
            nudes[i].right_i--;
            nudes[nudes[i].right_i].father_i = i;
        }
    }

    // stage 2: Children amount figuring out
    count_sub_size(nudes, 0);

    // stage 3: Deleting
    io >> M;
    for (int i = 0; i < M; ++i) {
        io >> bye_value;

        // stage 3.1: Searching certain node TODO USE MAP
        int cur_i = 0;
        while (cur_i != -1) {
            if (nudes[cur_i].value == bye_value) {
                int loss = nudes[cur_i].sub_size;
                cout << cur_i << endl;

                // stage 3.2: Removing relation TODO USE POINTERS INSTEAD OF ARRAY
                cur_i = nudes[cur_i].father_i;
                if (bye_value < nudes[cur_i].value) {
                    nudes[cur_i].left_i = 0;
                } else {
                    nudes[cur_i].right_i = 0;
                }

                // stage 3.3: Updating upper nodes counters TODO USE SIZEOF
                while (cur_i != -1) {
                    nudes[cur_i].sub_size -= loss;
                    cur_i = nudes[cur_i].father_i;
                }

                break;
            }
            if (bye_value < nudes[cur_i].value) {
                if (nudes[cur_i].left_i != 0) {
                    cur_i = nudes[cur_i].left_i;
                } else {
                    cur_i = -1;
                }
            } else {
                if (nudes[cur_i].right_i != 0) {
                    cur_i = nudes[cur_i].right_i;
                } else {
                    cur_i = -1;
                }
            }
        }
        io << nudes[0].sub_size << ' ';
    }

    return 0;
}
