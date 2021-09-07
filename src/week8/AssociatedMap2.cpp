#include <iostream>
#include <vector>
#include <functional>
#include <map>
#include <cmath>
#include "edx-io.hpp"

using namespace std;


enum Commands {
    GET = 1,
    PREV = 2,
    NEXT = 3,
    PUT = 4,
    DELETE = 5,
};


struct HashCode {
    int last;

    int (*hashFunction)(const string &);

    explicit HashCode(int (*hashFunction)(const string &)) : hashFunction(hashFunction) {}

    int operator()(const string &key) {
        return last = hashFunction(key);
    }
};


struct Cell {
    string key;
    string value;
    int hash = -1;
    int prev_index = -1;
    int next_index = -1;

    bool isEmpty() const {
        return hash == -1;
    }

    bool isMark() const {
        return hash == -2;
    }

    bool hasPrev() const {
        return prev_index != -1;
    }

    bool hasNext() const {
        return next_index != -1;
    }
};

struct SearchResult {
    int found = -1;
    int mark_hash = -1;
    int last_hash = -1;

    bool isFound() const {
        return found != -1;
    }

    bool hasMark() const {
        return mark_hash != -1;
    }
};

class AssociatedMap {
private:
    vector<Cell> table;
    HashCode hash1;
    HashCode hash2;
    int last_index;
    int element_count;

public:
    explicit AssociatedMap(int size, int (*hashFunction1)(const string &), int (*hashFunction2)(const string &))
            : table(size), hash1(hashFunction1), hash2(hashFunction2),
              last_index(-1), element_count(0)/*, blank_count(0)*/ {}

    string get(const string &key) {
        SearchResult result = search(key);
        if (result.isFound())
            return table[result.found].value;
        else
            return "<none>";
    }

    string previous(const string &key) {
        SearchResult result = search(key);
        if (result.isFound() && table[result.found].hasPrev())
            return table[table[result.found].prev_index].value;
        else
            return "<none>";
    }

    string next(const string &key) {
        SearchResult result = search(key);
        if (result.isFound() && table[result.found].hasNext())
            return table[table[result.found].next_index].value;
        else
            return "<none>";
    }

    void put(const string &key, const string &value) {      //TODO implement general search
        SearchResult result = search(key);
        if (result.isFound()) {
            table[result.found].value = value;
            return;
        }
        int index = (result.hasMark() ? result.mark_hash : result.last_hash) % table.size();
        table[index].key = key;
        table[index].value = value;
        table[index].hash = (result.hasMark() ? result.mark_hash : result.last_hash);
        table[index].prev_index = last_index;
        if (last_index != -1)
            table[last_index].next_index = index;
        last_index = index;
        element_count++;
        if (element_count > table.size() / 2)
            resize(2);
    }

    void remove(const string &key) {
        SearchResult result = search(key);
        if (result.isFound()) {
            int index = result.found;
            if (table[index].hasPrev())
                table[table[index].prev_index].next_index = table[index].next_index;
            if (table[index].hasNext())
                table[table[index].next_index].prev_index = table[index].prev_index;
            if (index == last_index)
                last_index = table[index].prev_index;
            table[index] = Cell();
            table[index].hash = -2;
            element_count--;
        }
    }

private:
    SearchResult search(const string &key) {
        SearchResult result;
        result.last_hash = hash1(key) + 0 * hash2(key);
        for (int iteration = 0, index = getIndex(iteration);
             !table[index].isEmpty();
             index = getIndex(++iteration), result.last_hash = getHash(iteration)) {
            if (table[index].hash == result.last_hash && table[index].key == key) {
                result.found = index;
                break;
            } else if (!result.hasMark() && table[index].isMark())
                result.mark_hash = result.last_hash;
        }
        return result;
    }

    void resize(int factor) {
        element_count = 0;
//        blank_count = 0;
        last_index = -1;
        auto old_table = table;
        table.clear();
        table.resize(old_table.size() * factor);
        for (int i = 0; i < old_table.size(); ++i) {
            if (!old_table[i].hasPrev() && old_table[i].hasNext()) {
                Cell old_element;
                for (old_element = old_table[i]; old_element.hasNext(); old_element = old_table[old_element.next_index])
                    put(old_element.key, old_element.value);
                put(old_element.key, old_element.value);
                break;
            }
        }
    }

    int getHash(int iteration) const {
        return hash1.last + iteration * hash2.last;
    }

    int getIndex(int iteration) const {
        return (hash1.last + iteration * hash2.last) % table.size();
    }
};

int main() {
    edx_io io;
    int N;
    string operation, key, value;
    map<string, int> commands{{"get",    GET},
                              {"prev",   PREV},
                              {"next",   NEXT},
                              {"put",    PUT},
                              {"delete", DELETE}};

    io >> N;
    AssociatedMap ass_map(4,
                          [](const string &key) {
                              int sum = 0;
                              for (int i = 0; i < key.size(); ++i)
                                  sum += key[i] * (i + 277);
                              return sum;
                          },
                          [](const string &key) {
                              int sum = 1;
                              for (int i = 1; i <= key.size(); ++i)
                                  sum += key[i] * pow(2, i);
                              return sum ;
                          });

    for (int i = 1; i <= N; ++i) {
        io >> operation >> key;
        switch (commands[operation]) {
            case GET:
                io << ass_map.get(key) << "\n";
                break;

            case PREV:
                io << ass_map.previous(key) << "\n";
                break;

            case NEXT:
                io << ass_map.next(key) << "\n";
                break;

            case PUT:
                io >> value;
                ass_map.put(key, value);
                break;

            case DELETE:
                ass_map.remove(key);
                break;
        }
    }

    return 0;
}