#include <iostream>
#include <string>
#include <queue>
using namespace std;

class HashTable {
public:
    HashTable();
    HashTable(string filename);

    string search(const string& key);
    void insert(const string& key, const string& value);
    string remove(const string& key);
    void display();

    unsigned int hash(const string& key);
    int search_index(const string& key, bool override_duplicated_key);

private:
    const static unsigned int size_max = 100;
    string keys[size_max];
    string values[size_max];
};

HashTable::HashTable() {
    for (int i = 0; i < size_max; i++) {
        keys[i] = string();
        values[i] = string();
    }
}

unsigned int HashTable::hash(const string& k)
{
    unsigned int value = 0 ;
    for (int i = 0; i < k.length(); i++)
        value = 37*value + k[i];
    return value;
}

void HashTable::display() {
    cout << "{";
    for (int i = 0; i < size_max; i++)
        if (!keys[i].empty())
            cout << keys[i] << ":" << values[i] << ", ";
    cout << "}" << endl;
}

int HashTable::search_index(const string& key, bool override_duplicate_key = true) {
    unsigned int h = hash(key) % size_max, offset = 0, index;

    while (offset < size_max) {
        index = (h + offset) % size_max;

        // if override_duplicate_key is false, return a new, unused index, used in hashTable
        if (keys[index].empty() || (override_duplicate_key && keys[index] == key))
            return index;

        offset++;
    }
    return -1;
}

void HashTable::insert(const string& key, const string& value) {
    int index = search_index(key);
    if (index == -1) {
        cerr << "Table is full!" << endl;
        return;
    }

    keys[index] = key;
    values[index] = value;
}

string HashTable::search(const string& key) {
    int index = search_index(key);
    if (index != -1)
        return values[index];

    return "";
}

string HashTable::remove(const string& key) {
    int index = search_index(key);
    if (index == -1) return "";

    string value = values[index];
    keys[index].clear();
    values[index].clear();

    return value;
}
