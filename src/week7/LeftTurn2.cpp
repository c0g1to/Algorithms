#include "edx-io.hpp"
#include <vector>
#include <iostream>
#include <climits>
#include <algorithm>
#include <queue>

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
    static int out_index;

public:
    explicit bin_tree(int size) {
        this->size = size;
        order = new node *[size + 1];
        reserve(1);
        root = order[1];
    }

    void insert_by_order(int index, int value, int left_index, int right_index) {
        order[index]->value = value;
        order[index]->left_child = reserve(left_index);
        order[index]->right_child = reserve(right_index);
    }

    void count_balance(node *current = nullptr) {
        if (current == nullptr) {
            current = root;
            height(current);
        }

        current->balance = (current->right_child == nullptr ? -1 : current->right_child->balance) -
                           (current->left_child == nullptr ? -1 : current->left_child->balance);

        if (current->left_child != nullptr)
            count_balance(current->left_child);
        if (current->right_child != nullptr)
            count_balance(current->right_child);
    }

    void balance(node *current = nullptr) {
        if (current == nullptr)
            current = root;

        if (current->left_child != nullptr)
            balance(current->left_child);
        if (current->right_child != nullptr)
            balance(current->right_child);

        turn(current);
    }

    void turn(node *A) {
        node *B = A->right_child;
        if (A->balance > 1) {
            if (B->balance == 0 || B->balance == 1)
                little_left_turn(A);
            else if (B->balance == -1)
                big_left_turn(A);
        }
        if (A->balance < -1) {
            if (B->balance == 0 || B->balance == -1)
                little_right_turn(A);
            else if (B->balance == 1)
                big_right_turn(A);
        }
    }

    explicit operator string() {
        string output = to_string(size) + "\n";
        int line = 1;
        queue<node *> node_queue;
        node_queue.push(root);
        while (!node_queue.empty()) {
            output += to_string(node_queue.front()->value) + " ";
            if (node_queue.front()->left_child != nullptr) {
                node_queue.push(node_queue.front()->left_child);
                output += to_string(++line) + " ";
            } else
                output += "0 ";
            if (node_queue.front()->right_child != nullptr) {
                node_queue.push(node_queue.front()->right_child);
                output += to_string(++line) + "\n";
            } else
                output += "0\n";
            node_queue.pop();
        }
        return output;
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

    void little_left_turn(node *A) {
        node *B = A->right_child;
        node *y = B->left_child;

        B->left_child = A;
        A->right_child = y;

        if (B->balance == 0) {
            A->balance = 1;
            B->balance = -1;
        } else {
            A->balance = 0;
            B->balance = 0;
        }

        if (root == A) {
            root = B;
        }
    }

    void little_right_turn(node *A) {
        node *B = A->left_child;
        node *y = B->right_child;

        B->right_child = A;
        A->left_child = y;

        if (B->balance == 0) {
            A->balance = -1;
            B->balance = 1;
        } else {
            A->balance = 0;
            B->balance = 0;
        }

        if (root == A) {
            root = B;
        }
    }

    void big_left_turn(node *A) {
        node *B = A->right_child;
        node *C = B->left_child;
        node *x = C->left_child;
        node *y = C->right_child;

        C->left_child = A;
        C->right_child = B;
        A->right_child = x;
        B->left_child = y;

        switch (C->balance) {
            case -1:
                A->balance = 0;
                B->balance = 1;
                break;

            case 0:
                A->balance = 0;
                B->balance = 0;
                break;

            case 1:
                A->balance = -1;
                B->balance = 0;
                break;
        }
        C->balance = 0;

        if (root == A) {
            root = C;
        }
    }

    void big_right_turn(node *A) {
        node *B = A->left_child;
        node *C = B->right_child;
        node *x = C->right_child;
        node *y = C->left_child;

        C->right_child = A;
        C->left_child = B;
        A->left_child = x;
        B->right_child = y;

        switch (C->balance) {
            case -1:
                A->balance = 1;
                B->balance = 0;
                break;

            case 0:
                A->balance = 0;
                B->balance = 0;
                break;

            case 1:
                A->balance = 0;
                B->balance = -1;
                break;
        }
        C->balance = 0;

        if (root == A) {
            root = C;
        }
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

    tree.count_balance();
    tree.balance();
    io << string(tree);

    tree.~bin_tree();
    return 0;
}
