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
#include <iostream>

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

    for (unsigned int i = 0;i < files.size();i++) {
        cout << i << files[i] << endl;
    }

    return 0;

}

