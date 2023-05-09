#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>

int main(int argc, char* argv[]){

    // open the directory
    DIR *dir;
    // variable to store a directory entry
    struct dirent *entry;

    dir = opendir(argv[1]);

    // loop over the directory
    while ((entry = readdir(dir)) != NULL) {
        // print directory contents
        printf("%s\n", entry->d_name);
    }

    // close the directory
    closedir(dir);

    return 0;
}