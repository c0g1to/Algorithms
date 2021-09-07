#include "edx-io.hpp"
#include <stack>
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

    Node *turn() {
        bool is_right;
        if (-1 <= balance && balance <= 1)
            return this;
        else {
            is_right = balance < -1;
            Node *B = children[!is_right];
            if (B->balance == (is_right ? 1 : -1))
                children[!is_right] = B->littleTurn(!is_right);
            if (-1 <= B->balance && B->balance <= 1)
                return littleTurn(is_right);
        }
        return nullptr;
    }

    Node *littleTurn(bool is_right) {
        Node *B = children[!is_right];
        children[!is_right] = B->children[is_right];
        B->children[is_right] = this;
        set_height()->set_balance();
        B->set_height()->set_balance();
        return B;
    }

    void hard_delete() {
        for (auto child : children)
            if (child != nullptr) {
                child->hard_delete();
                child = nullptr;
            }
        delete this;
    }
};


class AVLTree {
private:
    Node *root;
    Node **order;
    int size;
    inline static stack<Node *> search_stack;

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

    void remove(int value) {
        Node *removable = search(value, root);
        if (removable != nullptr) {
            --size;
            if (removable->children[0] != nullptr) {
                Node *replacement = removable->children[0];
                search_stack.push(removable);
                while (replacement->children[1] != nullptr) {
                    search_stack.push(replacement);
                    replacement = replacement->children[1];
                }
                swap(removable->value, replacement->value);
                swap(removable, replacement);
                search_stack.top()->children[replacement->children[0] != removable] = removable->children[0];
            } else {
                if (search_stack.empty())
                    root = removable->children[1];
                else
                    search_stack.top()->children[search_stack.top()->value < removable->value] = removable->children[1];
            }
            delete removable;
            removable = nullptr;
            adjust_by_stack();
        }
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
                child = child->turn();
            }
        if (current == root)
            root = root->turn();
    }

    explicit operator string() {
        string output = to_string(size) + "\n";
        if (size != 0) {
            queue<Node *> node_queue({root});
            for (int line = 1; !node_queue.empty();) {
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
        }
        return output;
    }

    ~AVLTree() {
        delete[] order;
        order = nullptr;
        if (size > 0) {
            root->hard_delete();
            root = nullptr;
        }
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
        if (value == current->value) {
            return current;
        } else {
            search_stack.push(current);
            int side = current->value < value;
            return (current->children[side] != nullptr
                    ? search(value, current->children[side])
                    : nullptr);
        }
    }

    void adjust_by_stack() {
        while (!search_stack.empty()) {
            Node *layer = search_stack.top();
            search_stack.pop();
            layer->set_height()->set_balance();
            if (search_stack.empty()) {
                root = layer->turn();
                break;
            } else
                search_stack.top()->children[search_stack.top()->value < layer->value] = layer->turn();
        }
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
    tree.remove(K);

    io << string(tree);
    return 0;
}