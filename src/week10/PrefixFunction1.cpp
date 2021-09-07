#include <vector>
#include "edx-io.hpp"

using namespace std;

int main() {
    edx_io io;
    string str;
    io >> str;
    vector<int> postfixes(str.size() + 1, 0);

    for (int i = 1, j = 0; i < str.size(); i += j == 0)
        for (j = postfixes[j]; str[i] == str[j]; ++j, ++i)
            postfixes[i + 1] = j + 1;

    for (int i = 1; i < postfixes.size(); ++i)
        io << postfixes[i] << " ";

    return 0;
}