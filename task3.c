#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FILE_PATH "/home/masha/Documents/SSA_pr9/testfile.txt"
#define COPY_PATH "/home/masha/Documents/SSA_pr9/copyfile.txt"

int main() {
    uid_t user_id = getuid(); 
    FILE *file = fopen(FILE_PATH, "w");
    if (!file) {
        perror("Failed to create file");
        return EXIT_FAILURE;
    }
    fprintf(file, "This is a test text file\n");
    fclose(file);

    if (setuid(0) == 0) {
        FILE *src_file = fopen(FILE_PATH, "r");
        FILE *dest_file = fopen(COPY_PATH, "w");
        if (src_file && dest_file) {
            char buffer[256];
            while (fgets(buffer, sizeof(buffer), src_file)) {
                fputs(buffer, dest_file);
            }
            fclose(src_file);
            fclose(dest_file);
            printf("File was successfully copied by root\n");
        } else {
            perror("Error copying file");
        }

        if (chown(COPY_PATH, user_id, user_id) != 0) {
            perror("Failed to change file ownership");
        }
    } else {
        printf("Error: Unable to obtain root privileges\n");
    }

    file = fopen(COPY_PATH, "w");
    if (!file) {
        perror("Unable to modify file");
    } else {
        fprintf(file, "New text\n");
        fclose(file);
        printf("File modified\n");
    }

    if (remove(COPY_PATH) == 0) {
        printf("File deleted\n");
    } else {
        perror("Failed to delete file");
    }

    return 0;
}
