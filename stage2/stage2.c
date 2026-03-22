#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include <sys/wait.h>   //wait and waitpid
#include <sys/types.h>  //pid_t
#include <unistd.h>     //fork,execvp
#include <stdlib.h>     //wait


int main(){
    char input[1024];

    while (1) {
        printf("myshell> ");
        fgets(input,sizeof(input),stdin);
        if (strcspn(input,"\n")==0)
            continue;
        input[strcspn(input,"\n")]=0;

        if (strcmp("exit",input)==0){
            printf("Halting!");
            break;
        }
            
        pid_t pid=fork();

        if (pid==0){
            char *args[]={input,NULL};
            execvp(args[0],args);

            printf("Invalid Command!\n");
            exit(1); //no exec run
        }
        else{
            wait(NULL);
        }
    }
}