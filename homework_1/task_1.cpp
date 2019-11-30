//Реализовать очередь с помощью двух стеков. Использовать стек, реализованный с помощью динамического буфера.
//Обрабатывать команды push back и pop front.

#include <iostream>
#include <cassert>
using namespace std;

class Stack {

    int buffer_size;
    int size;
    int * array;

    public:
        explicit Stack(int buffer_size);
        ~Stack();
        void increase_size();
        void decrease_size();
        bool is_empty();
        bool is_full();
        void push(int value);
        int pop();
};

class Queue {

    Stack input_stack;
    Stack output_stack;

    public:
        Queue(): input_stack(4), output_stack(4) {}
        void push(int value);
        int pop();
        bool is_empty();
};

Stack::Stack(int buffer_size) {
    this->buffer_size = buffer_size;
    array = new int[this->buffer_size];
    size = 0;
}

Stack::~Stack() {
    delete[] array;
}

void Stack::increase_size() {
    if (!is_full()) {
        return;
    }

    int * new_array = new int[2 * buffer_size];
    for (int i = 0; i < size; ++i) {
        new_array[i] = array[i];
    }
    delete[] array;

    array = new_array;
    buffer_size *= 2;
}

void Stack::decrease_size() {
    if (is_empty()) {
        return;
    }
    if (size > buffer_size / 2) {
        return;
    }

    int * new_array = new int[buffer_size / 2];
    for (int i = 0; i < size; ++i) {
        new_array[i] = array[i];
    }
    delete[] array;

    array = new_array;
    buffer_size /= 2;
}

bool Stack::is_empty() {
    return size == 0;
}

bool Stack::is_full() {
    return size == buffer_size;
}

void Stack::push(int value) {
    increase_size();
    array[size] = value;
    size += 1;
}

int Stack::pop() {

    decrease_size();

    if (is_empty()) {
        return -1;
    } else {
        size -= 1;
        return array[size];
    }
}

void Queue::push(int value) {
    input_stack.push(value);
}

int Queue::pop() {

    assert(!input_stack.is_empty() || !output_stack.is_empty());

    if (output_stack.is_empty()) {
        while (!input_stack.is_empty()) {
            output_stack.push(input_stack.pop());
        }
    }

    return output_stack.pop();
}

bool Queue::is_empty() {
    return input_stack.is_empty() && output_stack.is_empty();
}

int main() {

    Queue queue;

    int commands_count = 0;
    cin >> commands_count;

    int command = 0, value = 0;
    for (int i = 0; i < commands_count; ++i) {
        cin >> command >> value;

        if (command == 3) {
            queue.push(value);
        } else if (command == 2) {
            if (queue.is_empty()) {
                if (value != -1) {
                    cout << "NO";
                    return 0;
                }
            } else {
                if (value != queue.pop()) {
                    cout << "NO";
                    return 0;
                }
            }
        }
    }

    cout << "YES";

    return 0;
}
