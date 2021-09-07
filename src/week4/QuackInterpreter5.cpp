#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include "../mooc/edx-io.hpp"

using namespace std;

class quack_code_line {
private:
    string code_line;

public:
    quack_code_line& operator=(const string& line) {
        code_line = line;
        return *this;
    }

    explicit operator unsigned short() {
        return stoi(code_line);
    }

    char command() {
        return code_line[0];
    }

    char reg(int order = 1) {
        return code_line[order];
    }

    bool has_reg() {
        return code_line.size() > 1;
    }

    string label(int reg_quantity = 0) {
        return code_line.substr(1 + reg_quantity);
    }
};

class quack_machine {
private:
    vector<string> code;
    map<string, int> labels;
    map<char, unsigned short> registers;
    queue<unsigned short> memory;
    int line_pointer;
public:
    quack_code_line line;

    quack_machine() {
        line_pointer = -1;
    }

    bool next_line() {
        if (line_pointer + 1 < code.size()) {
            line = code[++line_pointer];
            return true;
        } else {
            return false;
        }
    }

    void go_to(const string& label) {
        line_pointer = labels[label];
    }

    void to_code(const string &line) {
        code.push_back(line);
        if (line[0] == ':') {
            labels[line.substr(1)] = code.size() - 1;
        }
    }

    unsigned short get() {
        unsigned short a = memory.front();
        memory.pop();
        return a;
    }

    void put(unsigned short value) {
        memory.push(value);
    }

    unsigned short read_reg(char location) {
        return registers[location];
    }

    void write_reg(char location, unsigned short value) {
        registers[location] = value;
    }

    void quit() {
        line_pointer = code.size();
    }
};

int main() {
    edx_io io = edx_io();
    string line;
    quack_machine m = quack_machine();

    io >> line;
    while (!line.empty()) {
        m.to_code(line);
        io >> line;
    }

    while (m.next_line()) {
        switch (m.line.command()) {
            case '+':
                m.put(m.get() + m.get());
                break;

            case '-':
                m.put(m.get() - m.get());
                break;

            case '*':
                m.put(m.get() * m.get());
                break;

            case '/':
                m.put(m.get() / m.get());
                break;

            case '%':
                m.put(m.get() % m.get());
                break;

            case '>':
                m.write_reg(m.line.reg(), m.get());
                break;

            case '<':
                m.put(m.read_reg(m.line.reg()));
                break;

            case 'P':
                if (m.line.has_reg()) {
                    io << m.read_reg(m.line.reg()) << '\n';
                } else {
                    io << m.get() << '\n';
                }
                break;

            case 'C':
                if (m.line.has_reg()) {
                    io << char(m.read_reg(m.line.reg()));
                } else {
                    io << char(m.get());
                }
                break;

            case ':':
                break;

            case 'J':
                m.go_to(m.line.label());
                break;

            case 'Z':
                if (m.read_reg(m.line.reg(1)) == 0) {
                    m.go_to(m.line.label(1));
                }
                break;

            case 'E':
                if (m.read_reg(m.line.reg(1)) == m.read_reg(m.line.reg(2))) {
                    m.go_to(m.line.label(2));
                }
                break;

            case 'G':
                if (m.read_reg(m.line.reg(1)) > m.read_reg(m.line.reg(2))) {
                    m.go_to(m.line.label(2));
                }
                break;

            case 'Q':
                m.quit();
                break;

            default:
                m.put((unsigned short)m.line);
                break;
        }
    }

    return 0;
}