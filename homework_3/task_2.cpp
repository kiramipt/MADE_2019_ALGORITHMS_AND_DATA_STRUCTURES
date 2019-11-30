//Солдаты. В одной военной части решили построить в одну шеренгу по росту. Т.к. часть была далеко не образцовая,
// то солдаты часто приходили не вовремя, а то их и вовсе приходилось выгонять из шеренги за плохо начищенные сапоги.
// Однако солдаты в процессе прихода и ухода должны были всегда быть выстроены по росту – сначала самые высокие,
// а в конце – самые низкие. За расстановку солдат отвечал прапорщик, который заметил интересную особенность –
// все солдаты в части разного роста. Ваша задача состоит в том, чтобы помочь прапорщику правильно расставлять солдат,
// а именно для каждого приходящего солдата указывать, перед каким солдатом в строе он должен становится.
//
//Вариант 7_1.  Требуемая скорость выполнения команды - O(log n) в среднем. В реализации используйте декартово дерево.

#include <iostream>
#include <random>
#include <stack>
using namespace std;

struct TreapNode {
    explicit TreapNode(int _key, int _priority) : key(_key), priority(_priority) {}
    ~TreapNode() {
        delete left;
        delete right;
    }

    int key = 0;
    int priority = 0;
    int children_count = 1;
    TreapNode * left = nullptr;
    TreapNode * right = nullptr;

    int get_children_count(TreapNode * node);
    void update(TreapNode * node);
};

int TreapNode::get_children_count(TreapNode * node) {
    if (!node)
        return 0;
    else
        return node->children_count;
}

void TreapNode::update(TreapNode * node) {
    if (!node)
        return;

    node->children_count = 1 + get_children_count(node->left) + get_children_count(node->right);
}

class Treap {
    public:
        ~Treap() {
            delete root;
        }
        void insert(int key, int priority);
        void erase(int position);
        int find_position(int key);
        void print_in_order();
        TreapNode * root = nullptr;
        static void split(TreapNode * node, int key, TreapNode * & left, TreapNode * & right);
        static TreapNode * merge(TreapNode * left, TreapNode * right);
        static TreapNode * erase(TreapNode * node, int key);
};

void Treap::split(TreapNode * node, int key, TreapNode * & left, TreapNode * & right) {
    if (!node) {
        left = right = nullptr;
    }
    else if (node->key < key) {
        split(node->right, key, node->right, right);
        left = node;
        left->update(left);
        right->update(right);
    }
    else {
        split(node->left, key, left, node->left);
        right = node;
        left->update(left);
        right->update(right);
    }
}

TreapNode * Treap::merge(TreapNode * left, TreapNode * right) {
    if (!left || !right) {
        return left == nullptr ? right : left;
    }

    if (left->priority > right->priority) {
        left->right = merge(left->right, right);
        left->update(left);
        return left;
    } else {
        right->left = merge(left, right->left);
        right->update(right);
        return right;
    }
}

void Treap::insert(int key, int priority) {

    auto * current_node = root;
    auto * prev_node = root;

    while (current_node && priority <= current_node->priority) {
        prev_node = current_node;
        if (key <= current_node->key) {
            current_node = current_node->left;
        }
        else {
            current_node = current_node->right;
        }
    }

    auto * node = new TreapNode(key, priority);
    split(current_node, key, node->left, node->right);

    if (current_node == root) {
        root = node;
    }
    else if (key <= prev_node->key) {
        prev_node->left = node;
    }
    else {
        prev_node->right = node;
    }
}

TreapNode * Treap::erase(TreapNode * node, int key) {
    if (!node)
        return node;

    if (node->key == key) {
        node = merge(node->left, node->right);
    } else {
        if (node->key > key)
            node->left = erase(node->left, key);
        else
            node->right = erase(node->right, key);
    }
    return node;
}

void Treap::erase(int position) {
    stack <TreapNode *> s;
    TreapNode * current_node = root;

    int current_position = 0;
    while (current_node != nullptr || !s.empty()) {

        while (current_node != nullptr) {
            s.push(current_node);
            current_node = current_node->left;
        }

        current_node = s.top();
        s.pop();

        if (current_position == position) {
            root = erase(root, current_node->key);
            return;
        }
        current_position += 1;
        current_node = current_node->right;
    }
}

void Treap::print_in_order() {
    stack <TreapNode *> s;
    TreapNode * current_node = root;

    while (current_node != nullptr || !s.empty()) {

        while (current_node != nullptr) {
            s.push(current_node);
            current_node = current_node->left;
        }

        current_node = s.top();
        s.pop();

        cout << current_node->key << " ";
        current_node = current_node->right;
    }
}

int Treap::find_position(int key) {
    stack <TreapNode *> s;
    TreapNode * current_node = root;

    int current_position = 0;
    while (current_node != nullptr || !s.empty()) {

        while (current_node != nullptr) {
            s.push(current_node);
            current_node = current_node->left;
        }

        current_node = s.top();
        s.pop();

        if (key == current_node->key) {
            return current_position;
        }

        current_position += 1;
        current_node = current_node->right;
    }
}

int main() {
//
//    int N = 0;
//    cin >> N;
//
//    auto * treap = new Treap();
//    int key = 0;
//    int command;
//    for (int i = 0; i < N; ++i) {
//        cin >> command >> key;
//        if (command == 1) {
//            // солдат с ростом X приходит в строй
//            treap->insert(-key, rand());
//            cout << treap->find_position(-key) << " ";
//
////            cout << key << " _ ";
////            treap->print_in_order();
////            cout << endl;
//
//        } else if (command == 2) {
//            // солдата, стоящим в строе на месте Y надо удалить из строя
//            treap->erase(key);
//        }
//    }

//    cout << endl;
//    treap->print_in_order();

    auto * treap = new Treap();

    treap->insert(2, 1000);
    treap->insert(1, 100);
    treap->insert(5, 100);
    treap->insert(3, 10);
    treap->insert(7, 10);


    treap->print_in_order();
    cout << endl;

//    treap->root = treap->root->update(treap->root);
//    cout << treap->root->get_children_count(treap->root);
//    cout << endl;




    auto * root = treap->root;
    auto * node = new TreapNode(8, 1);

    treap->split(root, node->key, root->left, root->right);
    root->left = treap->merge(root->left, node);
    root = treap->merge(root->left, node);

    treap->print_in_order();


//    cout << endl;
//    cout << treap->root->left->key << " " << endl;
//    cout << treap->root->right->key << " " << endl;;


//    auto * node = new TreapNode(key, priority);
//    split(current_node, key, node->left, node->right);


    return 0;
}