//Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы с открытой адресацией.
// Хранимые строки непустые и состоят из строчных латинских букв.
//Хеш-функция строки должна быть реализована с помощью вычисления значения многочлена методом Горнера.
//Начальный размер таблицы должен быть равным 8-ми. Перехеширование выполняйте при добавлении элементов в случае,
// когда коэффициент заполнения таблицы достигает 3/4.
//Структура данных должна поддерживать операции добавления строки в множество, удаления строки из множества и проверки
// принадлежности данной строки множеству.
//1_2. Для разрешения коллизий используйте двойное хеширование.

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int get_hash_1(const string & key, int m) {
    int hash = 0;
    for (auto c: key) {
        hash = (hash * 37 + c) % m;
    }
    return hash;
}

int get_hash_2(const string & key, int m) {
    int hash = 0;
    for (auto c: key) {
        hash = (hash * 137 + c) % m;
    }
    return 2 * hash + 1;
}

int d_hash(int hash_1, int hash_2, int i, int m) {
    return (hash_1 + i * hash_2) % m;
}

class HashTable {
public:
    explicit HashTable(int m_) : m(m_), table(m_), status(m_) {}
    bool has(const string & key) const;
    bool add(const string & key);
    bool remove(const string & key);

private:
    int m = 0;
    int number_of_elements = 0;
    int number_of_removed_elements = 0;
    vector <string> table;
    vector <int> status; // 0 - empty | 1 - ok | -1 - deleted
    void resize(int new_m);
};

bool HashTable::has(const string & key) const {

    int hash_1 = get_hash_1(key, m);
    int hash_2 = get_hash_2(key, m);

    for (int i = 0; i < m; ++i) {
        int hash = d_hash(hash_1, hash_2, i, m);

        if (status[hash] == 0) {
            return false;
        }

        if (table[hash] == key and status[hash] == 1) {
            return true;
        }
    }
    return false;
}

bool HashTable::add(const string & key) {

    if ((float) number_of_elements / (float) m >= 0.75) {
        resize(2 * m);
    }

    if ((float) number_of_removed_elements / (float) m > 0.5) {
        resize(m / 2);
    }

    int hash_1 = get_hash_1(key, m);
    int hash_2 = get_hash_2(key, m);

    int add_index = -1;
    for (int i = 0; i < m; ++i) {
        int hash = d_hash(hash_1, hash_2, i, m);

        if (table[hash] == key && status[hash] == 1) {
            return false;
        }

        if (status[hash] == 0 || status[hash] == -1) {
            add_index = hash;
            break;
        }
    }

    if(add_index == -1) {
        return false;
    }

    table[add_index] = key;
    status[add_index] = 1;
    number_of_elements += 1;

    return true;
}

bool HashTable::remove(const string & key) {
    if (!has(key)) {
        return false;
    }

    int hash_1 = get_hash_1(key, m);
    int hash_2 = get_hash_2(key, m);

    for (int i = 0; i < m; ++i) {
        int hash = d_hash(hash_1, hash_2, i, m);

        if (table[hash] == key) {
            status[hash] = -1;
            number_of_elements -= 1;
            number_of_removed_elements += 1;
            return true;
        }
    }
    return false;
}

void HashTable::resize(int new_m) {

    m = new_m;
    number_of_elements = 0;
    number_of_removed_elements = 0;

    vector <string> old_table = table;
    vector <int> old_status = status;

    table.resize(m);
    status.resize(m);

    for (size_t i = 0; i < table.size(); ++i) {
        status[i] = 0;
    }

    for (size_t i = 0; i < old_table.size(); ++i) {
        if (old_status[i] == 1) {
            add(old_table[i]);
        }
    }
}

int main() {

    HashTable table(8);

    char command = ' ';
    string value;
    while (cin >> command >> value) {
        switch (command) {
            case '?':
                cout << (table.has(value) ? "OK" : "FAIL") << endl;
                break;
            case '+':
                cout << (table.add(value) ? "OK" : "FAIL") << endl;
                break;
            case '-':
                cout << (table.remove(value) ? "OK" : "FAIL") << endl;
                break;
        }
    }
    return 0;
}