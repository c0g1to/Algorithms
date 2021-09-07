#include "edx-io.hpp"
#include <vector>
#include <iostream>

using namespace std;

int main() {
    edx_io io = edx_io();
    int n;
    double A;
    io >> n >> A;

    // stage 1: matrix coefficients calculating
    int zero_i = -1;
    vector<double> coefs(n), values(n);
    coefs[1] = -2;
    values[1] = 2 - A;
    for (int i = 2; i < coefs.size(); ++i) {
        coefs[i] = -2 - 1 / coefs[i - 1];
        values[i] = 2 - values[i - 1] / coefs[i - 1];

        // stage 1.1: zero index calculating
        if (values[i] > 0) {
            zero_i = i;
            break;
        }
    }

    // stage 2.1: short garland case
    if (zero_i == -1) {
        io << 0;
    } else {

    // stage 2.2: long garland case
        vector<double> heights(n);
        heights[zero_i] = 0;
        heights[zero_i - 1] = values[zero_i - 1] / coefs[zero_i - 1];
        for (int i = zero_i + 1; i < n; ++i) {
            heights[i] = 2 * heights[i - 1] - heights[i - 2] + 2;
        }
        io << heights[n - 1];
    }

    return 0;
}
