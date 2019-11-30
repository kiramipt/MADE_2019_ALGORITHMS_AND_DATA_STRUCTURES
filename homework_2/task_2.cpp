//Даны неотрицательные целые числа n,k и массив целых чисел из [0..10^9] размера n.
// Требуется найти k-ю порядковую статистику. т.е. напечатать число, которое бы стояло на позиции с индексом k (0..n-1)
// в отсортированном массиве. Напишите нерекурсивный алгоритм.
//Требования к дополнительной памяти: O(n). Требуемое среднее время работы: O(n).
//Функцию Partition следует реализовывать методом прохода двумя итераторами в одном направлении.
//
//4_1. Реализуйте стратегию выбора опорного элемента “медиана трёх”. Функцию Partition реализуйте методом прохода двумя
// итераторами от начала массива к концу.

#include <iostream>
using namespace std;

int median(const int * a, const int l, const int r) {

    int m = (l + r) / 2;

    // mlr || rlm
    if ((a[m] <= a[l] && a[l] <= a[r]) || (a[r] <= a[l] && a[l] <= a[m])) {
        return l;

    // lmr || rml
    } else if ((a[l] <= a[m] && a[m] <= a[r]) || (a[r] <= a[m] && a[m] <= a[l])) {
        return m;

    // lrm || mrl
    } else if((a[l] <= a[r] && a[r] <= a[m]) || (a[m] <= a[r] && a[r] <= a[l])) {
        return r;
    }
}

int partition(int * a, int l, int r) {

    swap(a[median(a, l, r)], a[r]);
    const int & pivot = a[r];

    int i = l, j = l;

    while (j < r) {
        if (a[j] <= pivot) {
            swap(a[i++], a[j]);
        }
        j++;
    }
    swap(a[i], a[r]);
    return i;
}

int k_stat_dc(int * a, int n, int k) {

    int l = 0, r = n - 1, p = 0;

    while (true) {
        p = partition(a, l, r);
        if (p == k) {
            break;
        } else if (p > k) {
            r = p - 1;
        } else {
            l = p + 1;
        }
    }
    return a[p];
}

int main() {

    int n = 0, k = 0;
    cin >> n >> k;

    int * a = new int[n];
    int e = 0;
    for (int i = 0; i < n; ++i) {
        cin >> e;
        a[i] = e;
    }

    cout << k_stat_dc(a, n, k);

    delete[] a;

    return 0;
}