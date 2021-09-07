#include <iostream>
#include <vector>
#include "../mooc/edx-io.hpp"

using namespace std;

int main() {
    edx_io io = edx_io();
    int n;
    io >> n;
    int *arr = new int[n + 1];
    for (int i = 1; i <= n; i++) {
        io >> arr[i];
    }

    for (int i = 1; i <= n / 2; i++) {
        if (arr[i] > arr[2 * i] || (2 * i + 1 <= n && arr[i] > arr[2 * i + 1])) {
            io << "NO";
            delete[] arr;
            return 0;
        }
    }

    io << "YES";
    delete[] arr;
    return 0;
}

