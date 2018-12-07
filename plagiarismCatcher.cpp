// plagiarismCatcher.cpp
//
// On our honor, this programming project is our own work and we have not
// provided this code to any other student.
//
// Troy Jackson and James Lin
//
// taj777 and jl62356
//
// Section 5 digit ID: 16240

#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <queue>
#include "hashTable.h"

using namespace std;

//Method provided in dir_help.cpp
//Fills a string vector with filenames from a directory input as a string
int getdir (string dir, vector<string> &files) {

    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(string(dirp->d_name));
    }
    closedir(dp);
    return 0;
}

//Helper function that removes all spaces and extraneous
//characters from the string to aid in plagiarism catching.
//Also changes all uppercase letters to lowercase.
string fixString(string word) {

    string fixed = "";
    char letter;

    for(int i = 0; i < word.length(); i++) {

        letter = word[i];
        switch(letter) {

            case 'A':
            case 'a': fixed = fixed + 'a';
                      break;
            case 'B':
            case 'b': fixed = fixed + 'b';
                      break;
            case 'C':
            case 'c': fixed = fixed + 'c';
                      break;
            case 'D':
            case 'd': fixed = fixed + 'd';
                      break;
            case 'E':
            case 'e': fixed = fixed + 'e';
                      break;
            case 'F':
            case 'f': fixed = fixed + 'f';
                      break;
            case 'G':
            case 'g': fixed = fixed + 'g';
                      break;
            case 'H':
            case 'h': fixed = fixed + 'h';
                      break;
            case 'I':
            case 'i': fixed = fixed + 'i';
                      break;
            case 'J':
            case 'j': fixed = fixed + 'j';
                      break;
            case 'K':
            case 'k': fixed = fixed + 'k';
                      break;
            case 'L':
            case 'l': fixed = fixed + 'l';
                      break;
            case 'M':
            case 'm': fixed = fixed + 'm';
                      break;
            case 'N':
            case 'n': fixed = fixed + 'n';
                      break;
            case 'O':
            case 'o': fixed = fixed + 'o';
                      break;
            case 'P':
            case 'p': fixed = fixed + 'p';
                      break;
            case 'Q':
            case 'q': fixed = fixed + 'q';
                      break;
            case 'R':
            case 'r': fixed = fixed + 'r';
                      break;
            case 'S':
            case 's': fixed = fixed + 's';
                      break;
            case 'T':
            case 't': fixed = fixed + 't';
                      break;
            case 'U':
            case 'u': fixed = fixed + 'u';
                      break;
            case 'V':
            case 'v': fixed = fixed + 'v';
                      break;
            case 'W':
            case 'w': fixed = fixed + 'w';
                      break;
            case 'X':
            case 'x': fixed = fixed + 'x';
                      break;
            case 'Y':
            case 'y': fixed = fixed + 'y';
                      break;
            case 'Z':
            case 'z': fixed = fixed + 'z';
                      break;
            case '0': fixed = fixed + '0';
                      break;
            case '1': fixed = fixed + '1';
                      break;
            case '2': fixed = fixed + '2';
                      break;
            case '3': fixed = fixed + '3';
                      break;
            case '4': fixed = fixed + '4';
                      break;
            case '5': fixed = fixed + '5';
                      break;
            case '6': fixed = fixed + '6';
                      break;
            case '7': fixed = fixed + '7';
                      break;
            case '8': fixed = fixed + '8';
                      break;
            case '9': fixed = fixed + '9';
                      break;
        }
    }

    return fixed;
}

//Creates a string key out of a queue containing n words
string createKey(queue<string> nwords) {
    
    string buf;
    string key = "";

    for(int i = 0; i < (nwords.size()); i++) {

        buf = nwords.front();
        key = key + buf;
        nwords.pop();
        nwords.push(buf);
    }

    return fixString(key);
}

int main(int argc, char *argv[]) {

    //Creates a hash table
    HashTable h;

    ifstream inputFile;
    queue <string> nwords;
    int qSize = atoi(argv[2]);
    int numSims = atoi(argv[3]);
    string buffer;

    //Creates a string and a vector to use for the getdir method
    string dir = argv[1];
    vector<string> files = vector<string>();

    //Gets filenames from the directory input in the command line
    //and puts them in the "files" vector
    getdir(dir,files);

    //Loops for each filename in the vector, except for the first two
    //This is because the first two are "." and ".."
    while((files.size()) > 2) {

        //Adds directory to front of filename in vector
        //This allows the file to be opened and read
        files[(files.size())-1] = dir + "/" + files[(files.size())-1];

        //Opens the file
        inputFile.open((files.back()).c_str());

        //cout << files.back() << endl;

        //Removes the filename from the end of the vector
        files.pop_back();
        if(inputFile.is_open()) {
            while(inputFile){

                inputFile >> buffer;

                if((nwords.size()) != qSize) {
                    nwords.push(buffer);   
                }
                else {
                    //cout << createKey(nwords) << endl;
                    h.insert(h.hash(createKey(nwords)), ((files.size()) - 1));
                    nwords.pop();
                    nwords.push(buffer);
                }
            }

            inputFile.close();
        }
        else {
            cout << "Error: File could not be opened." << endl;
        }
    }

    //h.findCols(files);

    return 0;
}

