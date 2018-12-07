#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int MAX = 200001;

class HashTable {
public:
    HashTable();
    void insert(const unsigned int key, const int value);
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

//The hash function
unsigned int HashTable::hash(const string& k)
{
    unsigned int value = 0 ;
    for (int i = 0; i < k.length(); i++)
        value = 37*value + k[i];
    return value;
}

//Helper function for insert
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

//Function for inserting values into the hash table
void HashTable::insert(const unsigned int key, const int value) {

    int index = search_index(key);
    if (index == -1) {
        cerr << "Table is full!" << endl;
        return;
    }
    keys[index] = key;
    values[index].push_back(value);
}

//Function that finds the collisions in the hash table and
//prints that information
void HashTable::findCols(vector<string> fileName, int compSize) {

    //Initializes 2D array to store number of collisions
    //between files
    int map[fileName.size()][fileName.size()];
    for (int i = 0; i < fileName.size(); i++) {
        for (int j = 0; j < fileName.size(); j++)
            map[i][j] = 0;      //i: row; j: col; map[row][col]
    }

    /* i: position in hash table (array)
     * j: element in value vector (map: row)
     * k: element in value vector (map: col)*/
    for (int i = 0; i < size_max; i++) {
        for (int j = 0; !values[i].empty() && (j < (values[i]).size()-1); j++) {
            for (int k = j+1; k < (values[i]).size(); k++) {
                map[values[i][k]][values[i][j]]++;
            }
        }
    }

    vector<int> colNums;
    vector<string> fileOne;
    vector<string> fileTwo;

    //Uses the map to fill the vectors with the information
    //indicating the amount of collisions between files
    for(int i = 2; i < fileName.size(); i++) {
        for(int j = (i+1); j < fileName.size(); j++) {
            if(map[i][j] >= compSize){ //Checks against input parameter
                colNums.push_back(map[i][j]);
                fileOne.push_back(fileName[i]); //Get file names
                fileTwo.push_back(fileName[j]); //
            }
        }
    }

    //Selection Sort
    int minData, tempData;
    int minIdx;
    string minPath1, minPath2, tempPath1, tempPath2;
    bool swapVar;

    for (int i = 0; i < colNums.size()-1; i++) {

        minData = colNums[i];
        minPath1 = fileOne[i];
        minPath2 = fileTwo[i];

        tempData = colNums[i];
        tempPath1 = fileOne[i];
        tempPath2 = fileTwo[i];

        swapVar = false;

        for (int j = i+1; j < colNums.size(); j++) {

            //Gets smallest in unsorted portion
            if (minData > colNums[j]) {
                minData = colNums[j];
                minPath1 = fileOne[j];
                minPath2 = fileTwo[j];
                minIdx = j;
                swapVar = true;
            }
        }

        //Swaps the elements of the vectors
        if(swapVar == true) {
        colNums[i] = minData;
        fileOne[i] = minPath1;
        fileTwo[i] = minPath2;
        colNums[minIdx] = tempData;
        fileOne[minIdx] = tempPath1;
        fileTwo[minIdx] = tempPath2;
        }
    }

    //Prints the sorted vectors
    cout << endl;
    for(int i=1; i <= colNums.size(); i++) {
        cout << colNums[colNums.size() - i] << " collisions: " 
             << fileOne[colNums.size() - i] << " and " 
             << fileTwo[colNums.size() - i] << endl;

    }
    cout << endl;

}

