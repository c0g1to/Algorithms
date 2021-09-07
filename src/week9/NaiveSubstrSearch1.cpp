#include <vector>
#include "edx-io.hpp"

using namespace std;


int main() {
    edx_io io;
    string sub, str;
    vector<int> entrances;
    io >> sub >> str;

    for (int i = 0, j; i < str.size(); ++i) {
            for (j = 0; j < sub.size() && str[i + j] == sub[j]; ++j) {}
            if (j == sub.size())
                entrances.push_back(i + 1);
    }

    io << entrances.size() << "\n";
    for (int entrance: entrances)
        io << entrance << " ";

    return 0;
}