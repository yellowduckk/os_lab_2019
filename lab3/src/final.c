#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Usage: %s seed array_size\n", argv[0]);
        return 1;
    }

    int seed = atoi(argv[1]);
    if (seed <= 0) {
        printf("Seed must be a positive number\n");
        return 1;
    }

    int array_size = atoi(argv[2]);
        if (array_size <= 0) {
        printf("Array size must be a positive number\n");
    return 1;
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
    // Child process
        char seed_str[12];
        char array_size_str[12];

        snprintf(seed_str, sizeof(seed_str), "%d", seed);
        snprintf(array_size_str, sizeof(array_size_str), "%d", array_size);

        execl("./sequential_min_max", "./sequential_min_max", seed_str, array_size_str, NULL);

        // execl fails
        perror("Exec failed");
        exit(1);
        
    } else {
    // Parent process
        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            int exit_status = WEXITSTATUS(status);
            if (exit_status == 0) {
                printf("Child process exited successfully\n");
            } else {
                printf("Child process exited with an error\n");
            }
        }
    }

    return 0;
}