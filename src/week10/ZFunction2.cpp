#include <vector>
#include <algorithm>
#include "edx-io.hpp"

using namespace std;

int main() {
    edx_io io;
    string str;
    int zL = 0, zR = 0;
    io >> str;
    vector<int> z(str.size(), 0);

    for (int i = 1, j; i < str.size(); ++i) {
        for (j = i < zR ? min(z[i - zL], zR - i) : 0; str[i + j] == str[j]; ++j) {}
        z[i] = j;
        if (i + j > zR) {
            zL = i;
            zR = i + j;
        }
    }

    for (int i = 1; i < z.size(); ++i)
        io << z[i] << " ";
    return 0;
}