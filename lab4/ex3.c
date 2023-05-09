#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    // structure to store file info
    struct stat file_info;

    // store file name
    char *filename = argv[1];

    // get details of a file
    if (lstat(filename, &file_info) == -1) {
        perror("lstat");
        exit(1);
    }

    printf("%s size: %ld bytes\n", filename, file_info.st_size);

    return 0;
}