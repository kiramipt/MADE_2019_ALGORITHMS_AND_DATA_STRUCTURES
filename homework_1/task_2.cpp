//Для сложения чисел используется старый компьютер. Время, затрачиваемое на нахождение суммы двух чисел равно их сумме.
// Таким образом для нахождения суммы чисел 1,2,3 может потребоваться разное время, в зависимости от порядка вычислений.
// ((1+2)+3) -> 1+2 + 3+3 = 9 ((1+3)+2) -> 1+3 + 4+2 = 10 ((2+3)+1) -> 2+3 + 5+1 = 11
// Требуется написать программу, которая определяет минимальное время, достаточное для вычисления суммы заданного
// набора чисел. Требуемое время работы O(n*log(n)).

#include <iostream>
#include <cassert>
#include <vector>
using namespace std;

class Heap {

    vector <int> vec;

public:
    void sift_down(int i);
    void sift_up(int i);
    int extract_min();
    void insert(int value);
    int size();
    bool empty();
};

void Heap::sift_down(int i) {
    int left, right, min;

    while (2 * i + 1 < vec.size()) {
        left = 2 * i + 1;
        right = 2 * i + 2;
        min = left;
        if (right < vec.size() && vec[right] < vec[left]) {
            min = right;
        }
        if (vec[i] <= vec[min]) {
            break;
        }
        swap(vec[i], vec[min]);
        i = min;
    }
}

void Heap::sift_up(int i) {
    while (vec[i] < vec[(i - 1) / 2]) {
        swap(vec[i], vec[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

int Heap::extract_min() {
    assert(!vec.empty());

    int min = vec[0];
    vec[0] = vec[vec.size() - 1];
    vec.pop_back();
    sift_down(0);
    return min;
}

int Heap::size() {
    return vec.size();
}

bool Heap::empty() {
    return vec.empty();
}

void Heap::insert(int value) {
    vec.push_back(value);
    sift_up(vec.size() -1);
}

int main() {

    int n = 0, e = 0;
    int answer = 0, e1 = 0, e2 = 0;
    Heap heap;

    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> e;
        heap.insert(e);
    }

    while (heap.size() > 1) {
        e1 = heap.extract_min();
        e2 = heap.extract_min();
        answer += e1 + e2;
        heap.insert(e1 + e2);
//        cout << e1 << ' ' << e2 << endl;
    }

    cout << answer;
}