#include "edx-io.hpp"
#include <vector>
#include <iostream>

using namespace std;

int main() {
    edx_io io = edx_io();
    int N, K, LR[2], max = 0;
    io >> N;
    vector<int> depths(N);

    if (N > 0) {
        depths[0] = 1;
        max = 1;
        for (int i = 0; i < N; ++i) {
            io >> K >> LR[0] >> LR[1];
            for (int child_index : LR) {
                if (child_index != 0) {
                    depths[child_index - 1] = depths[i] + 1;
                    if (depths[i] + 1 > max) {
                        max = depths[i] + 1;
                    }
                }
            }
        }
    }

    io << max;
    return 0;
}
