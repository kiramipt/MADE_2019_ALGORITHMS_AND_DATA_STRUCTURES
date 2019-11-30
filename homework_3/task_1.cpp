//Дано число N < 10^6 и последовательность целых чисел из [-2^31..2^31] длиной N.
//Требуется построить бинарное дерево, заданное наивным порядком вставки.
//Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K, то узел K добавляется в правое
// поддерево root; иначе в левое поддерево root.
//Рекурсия запрещена.
//
//6_2. Выведите элементы в порядке in-order (слева направо).

#include <iostream>
#include <stack>
using namespace std;

struct TreeNode {
    explicit TreeNode(int _value) : value(_value) {}
    ~TreeNode();

    int value = 0;
    TreeNode * left = nullptr;
    TreeNode * right = nullptr;
};

TreeNode::~TreeNode() {
    delete left;
    delete right;
}

class BinaryTree {
    public:
        ~BinaryTree();
        void print_in_order() const;
        void add(int value);

    private:
        TreeNode * root = nullptr;
};

BinaryTree::~BinaryTree() {
    delete root;
}

void BinaryTree::add(int value) {

    auto * node = new TreeNode(value);

    if (root == nullptr) {
        root = node;
        return;
    }

    TreeNode * current_node = root;

    while (true) {
        if (node->value >= current_node->value) {
            if (current_node->right == nullptr) {
                current_node->right = node;
                return;
            } else {
                current_node = current_node->right;
            }
        } else {
            if (current_node->left == nullptr) {
                current_node->left = node;
                return;
            } else {
                current_node = current_node->left;
            }
        }
    }

}

void BinaryTree::print_in_order() const {
    stack <TreeNode *> s;
    TreeNode * current_node = root;

    while (current_node != nullptr || !s.empty()) {

        while (current_node != nullptr) {
            s.push(current_node);
            current_node = current_node->left;
        }

        current_node = s.top();
        s.pop();

        cout << current_node->value << " ";

        current_node = current_node->right;
    }

}

int main() {

    BinaryTree tree;

    int N = 0;
    cin >> N;

    int value = 0;
    for (int i = 0; i < N; ++i) {
        cin >> value;
        tree.add(value);

    }

    tree.print_in_order();
    return 0;
}