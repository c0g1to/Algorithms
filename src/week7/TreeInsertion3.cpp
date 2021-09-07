#include "edx-io.hpp"
#include <vector>
#include <climits>
#include <algorithm>
#include <queue>

using namespace std;

class Node {
public:
    int value;
    Node *children[2];      // 0 - left child; 1 - right child
    int height;
    int balance;

    explicit Node(int value = INT_MIN, Node *left_child = nullptr, Node *right_child = nullptr) :
            value(value), height(0), balance(0) {
        children[0] = left_child;
        children[1] = right_child;
    }

    Node *set_balance() {
        balance = (children[1] == nullptr ? -1 : children[1]->height) -
                  (children[0] == nullptr ? -1 : children[0]->height);
        return this;
    }

    Node *set_height() {
        height = max(
                (children[0] == nullptr ? -1 : children[0]->height),
                (children[1] == nullptr ? -1 : children[1]->height)
        ) + 1;
        return this;
    }

    ~Node() {
        for (auto child : children) {
            delete child;
            child = nullptr;
        }
    }
};


class AVLTree {
private:
    Node *root;
    Node **order;
    int size;
    inline static vector<Node *> stray_path;

public:
    explicit AVLTree(int size) : size(size) {
        order = new Node *[size + 1];
        root = reserve(1);
    }

    void insertByOrder(int line, int value, int left_index, int right_index) {
        order[line]->value = value;
        order[line]->children[0] = reserve(left_index);
        order[line]->children[1] = reserve(right_index);
    }

    void insert(int value) {
        if (size == 0) {
            ++size;
            root->value = value;
        } else if (stray(value, root) != nullptr) {
            ++size;
            for (int i = stray_path.size() - 1; i >= 0; --i) {
                stray_path[i]->set_height()->set_balance();
                if (i == 0)
                    root = turn(stray_path[i]);
                else
                    stray_path[i - 1]->children[stray_path[i - 1]->value < stray_path[i]->value] = turn(stray_path[i]);
            }
        }
        stray_path.clear();
    }

    void adjust(Node *current = nullptr) {
        if (current == nullptr) {
            current = root;
            subHeight(root);
            subBalance(root);
        }
        for (auto child : current->children)
            if (child != nullptr) {
                adjust(child);
                child = turn(child);
            }
        if (current == root)
            root = turn(root);
    }

    Node *turn(Node *A) {
        bool is_right;
        if (-1 <= A->balance && A->balance <= 1)
            return A;
        else {
            is_right = A->balance < -1;
            Node *B = A->children[!is_right];
            if (B->balance == (is_right ? 1 : -1))
                A->children[!is_right] = littleTurn(B, !is_right);
            if (-1 <= B->balance && B->balance <= 1)
                return littleTurn(A, is_right);
        }
        return nullptr;
    }

    explicit operator string() {
        string output = to_string(size) + "\n";
        int line = 1;
        queue<Node *> node_queue({root});
        while (!node_queue.empty()) {
            output += to_string(node_queue.front()->value) + " ";
            for (int i = 0; i < 2; ++i) {
                if (node_queue.front()->children[i] != nullptr) {
                    node_queue.push(node_queue.front()->children[i]);
                    output += to_string(++line) + (i ? "\n" : " ");
                } else
                    output += (i ? "0\n" : "0 ");
            }
            node_queue.pop();
        }
        return output;
    }

    ~AVLTree() {
        delete[] order;
        order = nullptr;
        delete root;
        root = nullptr;
    }

private:
    Node *reserve(int index) {
        if (index != 0)
            return order[index] = new Node();
        return nullptr;
    }

    void applyToTree(Node *current, void (AVLTree::*func)(Node *)) {
        for (auto child : current->children)
            if (child != nullptr)
                (this->*func)(child);
    }

    void subBalance(Node *current) {
        applyToTree(current, &AVLTree::subBalance);
        current->set_balance();
    }

    void subHeight(Node *current) {
        applyToTree(current, &AVLTree::subHeight);
        current->set_height();
    }

    Node *search(int value, Node *current) {
        stray_path.push_back(current);
        if (value != current->value) {
            int side = current->value < value;
            return (current->children[side] != nullptr
                    ? stray(value, current->children[side])
                    : current->children[side] = new Node(value));
        }
        return nullptr;
    }

    Node *littleTurn(Node *A, bool is_right) {
        Node *B = A->children[!is_right];
        A->children[!is_right] = B->children[is_right];
        B->children[is_right] = A;
        A->set_height()->set_balance();
        B->set_height()->set_balance();
        return B;
    }
};


int main() {
    edx_io io = edx_io();
    int N, K, L, R;
    io >> N;
    AVLTree tree = AVLTree(N);

    for (int i = 1; i <= N; ++i) {
        io >> K >> L >> R;
        tree.insertByOrder(i, K, L, R);
    }

    tree.adjust();
    io >> K;
    tree.insert(K);

    io << string(tree);

    tree.~AVLTree();
    return 0;
}