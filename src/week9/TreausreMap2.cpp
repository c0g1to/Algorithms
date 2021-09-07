#include <vector>
#include "edx-io.hpp"

using namespace std;

int main() {
    edx_io io;
    string message, word;
    long long x = 0;
    vector<vector<int>> letter_positions(26);
    do {
        io >> word;
        message += word;
    } while (!word.empty());

    for (int i = 0; i < message.size(); ++i)
        letter_positions[message[i] - 97].push_back(i);

    for (auto & letter : letter_positions)
        for (int i = 0; i < letter.size(); ++i)
            x += letter[i] * (2 * i - letter.size() + 1) - i;

    io << x << "\n";
    return 0;
}