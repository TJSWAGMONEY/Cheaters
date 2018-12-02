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

using namespace std;

//Method provided in dir_help.cpp
//Fills a string vector with filenames from a directory input as a string
int getdir (string dir, vector<string> &files)
{
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

int main(int argc, char *argv[]) {

    //Creates a string and a vector to use for the getdir method
    string dir = argv[1];
    vector<string> files = vector<string>();

    //Gets filenames from the directory input in the command line
    //and puts them in the "files" vector
    getdir(dir,files);

    ifstream inputFile;
    queue <string> nwords;
    int qSize = atoi(argv[2]);
    string buffer;

    while((files.size()) > 0) {

        //Adds directory to front of filename in vector
        //This allows the file to be opened and read
        files[(files.size())-1] = dir + "/" + files[(files.size())-1];

        //Opens the file
        inputFile.open((files.back()).c_str());

        //cout << files.back() << endl;    //Prints the file it's opening

        //Removes the filename from the end of the vector
        files.pop_back();

        if(inputFile.is_open()) {

            inputFile >> buffer; //this is the line that isn't working
            //Trying to read word by word from input file into queue
            //After the first case (when it hits n words) the queue
            //  will iterate through the file and put n-word frames
            //  into the hash function hash()
            //We also need to remove punctuation (probably in buffer string)
            //  and make all of the letters uppercase (can use helper function
            //  for that)
            //We're then gonna take the integer from the hash and use it to
            //  put the filename in the hash table

        }
        else {
            cout << "Error: File could not be opened." << endl;
        }

    }

/*  for (unsigned int i = 0;i < files.size();i++) {    //Tests if getdir is working
        cout << i << files[i] << endl;
    }
*/

    return 0;

}

