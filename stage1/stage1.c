#include <stdio.h>
#include <string.h>
#include <ctype.h>

void lowerInput(char *arr){
    int i=0;
    while (arr[i]!='\0'){
        if (isalpha(arr[i])){
            arr[i]=tolower(arr[i]);
        }
        i++;
    }
}

void printHelp(){
    printf(" exit - halting \n ls - list all the files and folders ");
}

int main(){
    char input[1024];

    while (1) {
        printf("myshell> ");
        fgets(input,sizeof(input),stdin);
        if (strcspn(input,"\n")==0)
            continue;
        input[strcspn(input,"\n")]=0;

        if (!strcmp("help",input) || !strcmp("h",input))
            printHelp();

        char check[1024];
        strcpy(check,input);
        lowerInput(check);

        if (strcmp("exit",check)==0){
            printf("Halting!");
            break;
        }
            
        
        printf("%s\n",input);
    }
}