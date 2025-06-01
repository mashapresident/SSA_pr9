#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pids[10];

    for (int i = 0; i < 10; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            printf("Child %d started with PID %d\n", i, getpid());
            exit(0);
        } else {
            pids[i] = pid;
        }
    }
    sleep(3);
    
    printf("\n");
    for (int i = 0; i < 10; i++) {
        int status;
        pid_t pid = wait(&status);
        if (WIFEXITED(status)) {
            printf("child %d (PID %d) exited with code %d\n", i, pids[i], WEXITSTATUS(status));
        }
    }
    return 0;
}
