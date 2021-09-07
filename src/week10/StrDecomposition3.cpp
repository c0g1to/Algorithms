#include <vector>
#include <map>
#include <algorithm>
#include <stdexcept>
#include "edx-io.hpp"

//UNFINISHED
using namespace std;

struct SuperChar {
    inline static int next_id;
    int id;
    string symbols;
    int gr_len;
    int gr_id;

    explicit SuperChar(int id = 0, string symbols = "") : id(id), symbols(move(symbols)), gr_len(1), gr_id(id) {}
};

int main() {
    edx_io io;
    SuperChar::next_id = 1001;
    string raw_str;
    bool final = false;
    int iterations = 0;
    map<int, int> last_entrances;   //TODO wrong logic
    vector<SuperChar> str;
    io >> raw_str;

    //1 String to SuperChar vector converting
    str.reserve(raw_str.size());
    for (char &sym : raw_str)
        str.emplace_back(sym, string(1, sym));

    //2 Folding
    while (!final) {
        final = true;
        //2.1 Group marking
        for (int i = 0; i < str.size();) {
            try {
                //2.1.1 Last entrances manipulations
                int j = last_entrances.at(str[i].id);
                if (str[i].id == str[i - 1].id) {   //TODO improve logic
                    ++i;
                    continue;
                }
                last_entrances[str[i].id] = i;
                //2.1.2 New group size computation
                int beg_i_n = i++, beg_j_n = j++;
                for (; str[i].id == str[j].id && j < beg_i_n; ++i, ++j)
                    str[beg_i_n].gr_len++;
                //2.1.3 New group id assigning
                if (str[beg_j_n].gr_len == 1)
                    str[beg_j_n].gr_len = str[beg_i_n].gr_len;
                if (str[beg_i_n].gr_len != 1 && str[beg_i_n].gr_len == str[beg_j_n].gr_len) {
                    if (str[beg_j_n].gr_id == str[beg_j_n].id)
                        str[beg_j_n].gr_id = SuperChar::next_id++;
                    str[beg_i_n].gr_id = str[beg_j_n].gr_id;
                }
            } catch (out_of_range &) {
                last_entrances[str[i].id] = i;
                ++i;
            }
        }

        //2.2 Grouping
        vector<SuperChar> new_str;
        for (int i = 0; i < str.size(); i += str[i].gr_len) {
            string new_group;
            for (int j = 0; j < str[i].gr_len; ++j)
                new_group += str[i + j].symbols;
            new_str.emplace_back(str[i].gr_id, new_group);
        }
        final = str.size() == new_str.size();
        str = new_str;
        ++iterations;
    }

    //3 Expanding //TODO improve logic
    if (iterations == 1) {
        io << raw_str;
    } else {
        int repetition = 1;
        for (int i = 1; i < str.size(); ++i) {
            if (str[i].id == str[i - 1].id) {
                ++repetition;
            } else {
                io << str[i - 1].symbols << (repetition == 1 ? "" : "*" + to_string(repetition)) << "+";
                repetition = 1;
            }
        }
        io << str[str.size() - 1].symbols << (repetition == 1 ? "" : "*" + to_string(repetition));
    }

    return 0;
}