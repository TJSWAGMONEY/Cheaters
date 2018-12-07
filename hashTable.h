#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int MAX = 100003;

class HashTable {
public:
    HashTable();
/*    string remove(const int key);
    string search(const int key);*/
    void insert(const int key, const int value);
    void findCols(vector<string> fileName, int compSize);
    unsigned int hash(const string& key);
    int search_index(const int key, bool dupKeyFlag);

private:
    const static unsigned int size_max = MAX;
    int keys[size_max];
    vector<int> values[size_max];
};

HashTable::HashTable() {
    for (int i = 0; i < size_max; i++) {
        keys[i] = -1;
        vector<int> myPath;
        values[i] = myPath;
    }
}

unsigned int HashTable::hash(const string& k)
{
    unsigned int value = 0 ;
    for (int i = 0; i < k.length(); i++)
        value = 37*value + k[i];
    return value;
}

int HashTable::search_index(const int key, bool dupKeyFlag = true) {
    unsigned int h = hash(to_string(static_cast<long long>(key))) % size_max;
    unsigned int offset = 0;
    unsigned int index;

    while (offset < size_max) {
        index = (h + offset) % size_max;

        // if dupKeyFlag is false, return a new, unused index, used in hashTable
        if (keys[index] == -1 || dupKeyFlag && keys[index] == key)
            return index;

        offset++;
    }
    return -1;
}

void HashTable::insert(const int key, const int value) {
    int index = search_index(key);
    if (index == -1) {
        cerr << "Table is full!" << endl;
        return;
    }

    keys[index] = key;
    values[index].push_back(value);
}

void HashTable::findCols(vector<string> fileName, int compSize) {
    int map[fileName.size()][fileName.size()];
    for (int i = 0; i < fileName.size(); i++) {
        for (int j = 0; j < fileName.size(); j++)
            map[i][j] = 0;      //i: row; j: col; map[row][col]
    }

    /* i: position in hash table (array)
     * j: element in value vector (map: row)
     * k: element in value vector (map: col)*/
    for (int i = 0; i < size_max; i++) {
        for (int j = 0; j < values[i].size()-1; j++)
            for (int k = j+1; k < values[i].size(); k++)
                map[values[i][k]][values[i][j]]++;
    }

//
    for(int i=0; i < colNums.size(); i++) {
        cout << colNums[i] << " collisions: " << fileOne[i] << " and " << fileTwo[i] << endl;
    }
//
    vector<int> colNums;
    vector<string> fileOne;
    vector<string> fileTwo;

    for(int i = 2; i < fileName.size(); i++) {
        for(int j = (i+1); j < fileName.size(); j++) {
            if(map[i][j] >= compSize){
                colNums.push_back(map[i][j]);
                fileOne.push_back(fileName[i]);
                fileTwo.push_back(fileName[j]);
            }
        }
    }
}

/*
string HashTable::search(const int key) {
    int index = search_index(key);
    if (index != -1)
        return values[index];

    return "";
}

string HashTable::remove(const int key) {
    int index = search_index(key);
    if (index == -1) return "";

    string value = values[index];
    keys[index].clear();
    values[index].clear();

    return value;
}*/
