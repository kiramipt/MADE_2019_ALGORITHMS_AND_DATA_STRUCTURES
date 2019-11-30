//3_1. Первые k элементов длинной последовательности.
//Дана очень длинная последовательность целых чисел длины n.
// Требуется вывести в отсортированном виде её первые k элементов. Последовательность может не помещаться в память.
// Время работы O(n * log(k)). Память O(k). Использовать слияние.

#include <iostream>
#include <cstring>

using namespace std;

void merge(const int * arr_1, int arr_1_size, const int * arr_2, int arr_2_size, int * result) {

    int i = 0, j = 0;

    while (i < arr_1_size && j < arr_2_size) {
        if (arr_1[i] <= arr_2[j]) {
            result[i+j] = arr_1[i];
            ++i;
        } else {
            result[i+j] = arr_2[j];
            ++j;
        }
    }

    if (i == arr_1_size) {
        for (; j < arr_2_size; ++j) {
            result[i+j] = arr_2[j];
        }
    } else if (j == arr_2_size) {
        for (; i < arr_1_size; ++i) {
            result[i+j] = arr_1[i];
        }
    }

}

void merge_sort(int * a, int size) {

    if (size <= 1) {
        return;
    }

    int left_part_size = size / 2;
    int right_part_size = size - left_part_size;

    merge_sort(a, left_part_size);
    merge_sort(a + left_part_size, right_part_size);

    int * new_a = new int[size];
    merge(a, left_part_size, a + left_part_size, right_part_size, new_a);
    memcpy(a, new_a, sizeof(int) * size);
    delete[] new_a;
}


void my_merge(int * result_data, int * rolling_data, int k) {

    int * temp_data = new int[2*k];
    merge(result_data, k, rolling_data, k, temp_data);

    for (int i = 0; i < k; ++i) {
        result_data[i] = temp_data[i];
    }
    delete[] temp_data;
}

int main() {

    int n = 0, k = 0;
    cin >> n >> k;

    int * result_data = new int[k];
    int * rolling_data = new int[k];

    int e = 0;
    for (int i = 0; i < k; ++i) {
        cin >> e;
        result_data[i] = e;
    }
    merge_sort(result_data, k);

    for (int i = k; i < n; ++i) {
        cin >> e;
        rolling_data[i % k] = e;

        if ((i + 1) % k == 0 || i == n - 1) {
            merge_sort(rolling_data, k);
            my_merge(result_data, rolling_data, k);
        }
    
    }

    for (int i = 0; i < k; ++i) {
        cout << result_data[i] << ' ';
    }

    delete[] result_data;
    delete[] rolling_data;

    return 0;
}