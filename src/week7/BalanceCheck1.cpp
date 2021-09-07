#include "edx-io.hpp"
#include <vector>
#include <iostream>
#include <climits>
#include <algorithm>

using namespace std;


struct node {
    int value;
    node *left_child;
    node *right_child;
    int balance;

    explicit node(int value = INT_MIN, node *left_child = nullptr, node *right_child = nullptr) :
            value(value), left_child(left_child), right_child(right_child), balance(INT_MIN) {}

    ~node() {
        delete left_child;
        left_child = nullptr;
        delete right_child;
        right_child = nullptr;
    }
};


class bin_tree {
private:
    node *root;
    node **order;
    int size;

public:
    explicit bin_tree(int size) {
        this->size = size;
        order = new node *[size + 1];
        reserve(1);
        root = order[1];
    }

    void insertByOrder(int index, int value, int left_index, int right_index) {
        order[index]->value = value;
        order[index]->left_child = reserve(left_index);
        order[index]->right_child = reserve(right_index);
    }

    void adjust(node *current = nullptr) {
        if (current == nullptr) {
            current = root;
            height(current);
        }

        current->balance = (current->right_child == nullptr ? -1 : current->right_child->balance) -
                           (current->left_child == nullptr ? -1 : current->left_child->balance);

        if (current->left_child != nullptr)
            balance(current->left_child);
        if (current->right_child != nullptr)
            balance(current->right_child);
    }

    int get_balance(int index) {
        return order[index]->balance;
    }

    ~bin_tree() {
        delete[] order;
        order = nullptr;
        delete root;
        root = nullptr;
    }

private:
    node *reserve(int index) {
        if (index != 0) {
            node *free_node = new node();
            order[index] = free_node;
            return free_node;
        }
        return nullptr;
    }

    int height(node *current) {
        current->balance = max(
                (current->left_child == nullptr ? -1 : height(current->left_child)),
                (current->right_child == nullptr ? -1 : height(current->right_child))
        ) + 1;
        return current->balance;
    }
};


int main() {
    edx_io io = edx_io();
    int N, K, L, R;
    io >> N;
    bin_tree tree = bin_tree(N);

    for (int i = 1; i <= N; ++i) {
        io >> K >> L >> R;
        tree.insert_by_order(i, K, L, R);
    }

    tree.balance();
    for (int i = 1; i <= N; ++i) {
        io << tree.get_balance(i) << '\n';
    }

    tree.~bin_tree();
    return 0;
}
