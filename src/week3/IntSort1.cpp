#include <iostream>
#include "../mooc/edx-io.hpp"

using namespace std;

void read_to_array(const edx_io &io, int *arr, int size) {
    for (int i = 0; i < size; i++) {
        io >> arr[i];
    }
}

//copy-pasted
int digit(int n, int k, int N, int M) {
    return (n >> (N * k) & (M - 1));
}

//copy-pasted
void radixsort(long *l, long *r, int N) {
    int k = (32 + N - 1) / N;
    int M = 1 << N;
    int sz = r - l;
    long *b = new long[sz];
    long *c = new long[M];
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < M; j++)
            c[j] = 0;
        for (long *j = l; j < r; j++)
            c[digit(*j, i, N, M)]++;
        for (int j = 1; j < M; j++)
            c[j] += c[j - 1];
        for (long *j = r - 1; j >= l; j--)
            b[--c[digit(*j, i, N, M)]] = *j;
        int cur = 0;
        for (long *j = l; j < r; j++)
            *j = b[cur++];
    }
    delete b;
    delete c;
}

int main() {
    edx_io io = edx_io();
    int n, m;
    long long sum = 0;

    io >> n >> m;
    int *arr1 = new int[n];
    int *arr2 = new int[m];
    long *merged_arr = new long[m * n];

    read_to_array(io, arr1, n);
    read_to_array(io, arr2, m);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            merged_arr[i * m + j] = arr1[i] * arr2[j];
        }
    }

    radixsort(merged_arr, merged_arr + n * m, sizeof(long));

    for (int i = 0; i < m * n; i += 10) {
        sum += merged_arr[i];
    }

    io << sum;

    delete[] arr1;
    delete[] arr2;
    delete[] merged_arr;
    return 0;
}
