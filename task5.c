#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#define TEMP_FILE "/home/masha/Documents/SSA_pr9/testfile.txt"

int main() {
    uid_t user_id = getuid();

    FILE *file = fopen(TEMP_FILE, "w");
    if (!file) {
        perror("Failed to create temporary file");
        return EXIT_FAILURE;
    }
    fprintf(file, "This is a test temporary file.\n");
    fclose(file);
    printf("Temporary file created successfully.\n");

    if (setuid(0) == 0) {
        printf("Switched to root.\n");

        if (chown(TEMP_FILE, user_id, user_id) != 0) {
            perror("Failed to change file ownership");
        } else {
            printf("File ownership changed.\n");
        }

        if (chmod(TEMP_FILE, 0400) != 0) {
            perror("Failed to change file permissions");
        } else {
            printf("File permissions changed to read-only for owner.\n");
        }
    } else {
        printf("Unable to obtain root privileges.\n");
    }

    file = fopen(TEMP_FILE, "r");
    if (file) {
        printf("User can read the file.\n");
        fclose(file);
    } else {
        perror("User cannot read the file");
    }

    file = fopen(TEMP_FILE, "w");
    if (file) {
        printf("User can write to the file.\n");
        fclose(file);
    } else {
        perror("User cannot write to the file");
    }

    return 0;
}
