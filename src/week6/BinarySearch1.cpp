#include "edx-io.hpp"
#include <vector>

using namespace std;

int main() {
    edx_io io = edx_io();
    int n, m, request;

    io >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        io >> arr[i];
    }

    io >> m;
    for (int i = 0; i < m; i++) {
        int left = -1, right = n, middle, left_border, right_border;
        io >> request;

        left = -1, right = n;
        while (left + 1 < right) {
            middle = (left + right) / 2;
            if (arr[middle] < request) {
                left = middle;
            } else {
                right = middle;
            }
        }
        if (arr[right] != request) {
            io << "-1 -1\n";
            continue;
        }
        io << right + 1 << ' ';

        left = -1, right = n;
        while (left + 1 < right) {
            middle = (left + right) / 2;
            if (arr[middle] <= request) {
                left = middle;
            } else {
                right = middle;
            }
        }
        io << left + 1 << '\n';


//        // searching middle index
//        while (left + 1 < right) {
//            middle = (left + right) / 2;
//            if (arr[middle] < request) {
//                left = middle;
//            } else {
//                if (arr[middle] == request) {
//                    left_border = middle;
//                    right_border = right;
//                    break;
//                } else {
//                    right = middle;
//                }
//            }
//        }
//
//        // bad request
//        if (left + 1 >= right) {
//            io << "-1 -1\n";
//            continue;
//        }
//
//        // left index searching
//        right = middle;
//        while (left + 1 < right) {
//            middle = (left + right) / 2;
//            if (arr[middle] == request) {
//                right = middle;
//            } else {
//                left = middle;
//            }
//        }
//        io << right + 1 << ' ';
//
//        // right index searching
//        right = right_border;
//        left = left_border;
//        while (left + 1 < right) {
//            middle = (left + right) / 2;
//            if (arr[middle] == request) {
//                left = middle;
//            } else {
//                right = middle;
//            }
//        }
//        io << left + 1 << '\n';
    }

    return 0;
}
