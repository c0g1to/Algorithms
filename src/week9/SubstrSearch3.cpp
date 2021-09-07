#include <vector>
#include "edx-io.hpp"

using namespace std;

int main() {
    edx_io io;
    string sub, str;
    io >> sub >> str;
    str = sub + "#" + str;
    vector<int> postfixes(str.size() + 1, 0);
    vector<int> entrances;

    for (int i = 1, j = 0; i < str.size(); i += j == 0)
        for (j = postfixes[j]; str[i] == str[j]; ++j, ++i)
            postfixes[i + 1] = j + 1;

    for (int i = 1; i <= postfixes.size(); ++i)
        if (postfixes[i] == sub.size())
            entrances.push_back(i - 2 * sub.size());

    io << entrances.size() << "\n";
    for (int entrance : entrances)
        io << entrance << " ";
    return 0;
}