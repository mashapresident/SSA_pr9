#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

void list_files(const char *path) {
    printf("\nListing files in: %s\n", path);
    char command[256];
    snprintf(command, sizeof(command), "ls -l %s", path);
    system(command);
}

void check_access(const char *file) {
    printf("\nChecking access for file: %s\n", file);

    if (access(file, R_OK) == 0) {
        printf("Can read the file.\n");
    } else {
        perror("Cannot read the file");
    }

    if (access(file, W_OK) == 0) {
        printf("Can write to the file.\n");
    } else {
        perror("Cannot write to the file");
    }

    if (access(file, X_OK) == 0) {
        printf("Can execute the file.\n");
    } else {
        perror("Cannot execute the file");
    }
}

int main() {
    list_files(getenv("HOME"));
    list_files("/usr/bin");
    list_files("/etc");

    check_access("/etc/passwd");
    check_access("/usr/bin/ls");

    return 0;
}
