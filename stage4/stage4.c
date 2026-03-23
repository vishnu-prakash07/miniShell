#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(){
    char input[1024];

    while (1) {
        printf("myshell> ");
        fgets(input, sizeof(input), stdin);

        if (input[0] == '\n')
            continue;

        input[strcspn(input, "\n")] = 0;
        
        char *args[100];
        int i = 0;

        args[i] = strtok(input, " ");

        while (args[i] != NULL){
            i++;
            args[i] = strtok(NULL, " ");
        }

        // ✅ correct null check
        if (args[0] == NULL)
            continue;

        // exit
        if (strcmp("exit", args[0]) == 0){
            printf("Halting!\n");
            break;
        }

        // cd
        if (strcmp("cd", args[0]) == 0){
            if (args[1] == NULL){
                printf("cd: missing argument\n");
            }
            else{
                if (chdir(args[1]) != 0){
                    printf("cd failed\n");
                }
            }
            continue;
        }

        pid_t pid = fork();

        if (pid == 0){
            execvp(args[0], args);
            perror("Invalid Command");
            exit(1);
        }
        else{
            wait(NULL);
        }
    }
}