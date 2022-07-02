#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define  SIZE 255 
#define MAX_TODOS 99

char * capitalize(char * input) {

    for(int i = 0; input[i] != '\0'; i++) {
        if(i == 0)
            input[i] = toupper(input[0]);  
        else 
            input[i] = tolower(input[i]);  
    }
    return input;
}

void create(char **array, int i, char *input, int size) {
    FILE *fp;
    fp = fopen("todos.dat", "w");

    array[i] = malloc(size*sizeof(char));
    capitalize(input);
    strcpy(array[i], input);

    for(int j = 0; j <= i; j++) {
        fprintf(fp, array[j]);
        fprintf(fp, "\n");
    }
    fclose(fp);
}

void read(char **array, int line) {

    if(array[0] == 0)
        printf("| -- |             *****              |   --   |\n");

    for(int i = 0; i < line; i++) {
        if(strlen(array[i]) > 27) {

            char str[50];
            for(int j = 0; j < 27; j++ ) str[j] = array[i][j];
            for(int k = 27; k < 30; k++ ) str[k] = '.';
            printf("| 0%-2d| %-30s |   %s   |\n", i+1, str, "--");

        } else {
            printf("| 0%-2d| %-30s |   %s   |\n", i+1, array[i], "--");
        }
    }
}

void delete(char **array, int line) {
    printf("Whitch line?\n\n");
}

void clear(char **array, int line) {
    // Clear todos.dat file
    FILE *fp;
    fp = fopen("todos.dat", "w");
    fclose(fp);
    
    //Clear array of todos
    //memset(array, 0, sizeof(array));
    for(int i = 0; i < line; i++) free(array[i]);
    main();
}

void commandLine(char **array, int line) {
    char input[SIZE];
    int size;

    printf("  ✎ -> ");
    //✎
    gets(input);
    size = strlen(input);
    
    //Todo -> Fix: "m" is also beeing accepted!
    if(strcmp(input, "clear") == 0 ) {
        clear(array, line);
    // } else if (strcmp(input, "del") == 0) {
    //     printf("Whitch line?\n\n");
    //     //delete(array, line);
    } else {
        //remove new line character
        input[strcspn(input, "\n")] = 0;
        create(array, line, input, size);
    }
}

int main () {

    char str[SIZE];
    char *array[MAX_TODOS];
    array[0] = 0;
    FILE *fp;
    int line = 0, i = 0;

    if(!(fp = fopen("todos.dat", "r"))) {
        fp = fopen("todos.dat", "w");
    }

    //read file todos and save in the array
    while(fgets(str, SIZE, fp)) {
        //Remove new line character from each end of line
        str[strcspn(str, "\n")] = 0;

        array[i] = malloc(strlen(str) * sizeof(char));
        strcpy(array[i], str);
        i++;
        line++;
    }

    fclose(fp); 

    while(1) {
        system("clear");
        printf("+----------------------------------------------+\n");
        printf("| N° |            Taskmemo            | Status |\n");
        printf("+----+--------------------------------+--------+\n");
        read(array, line);
        printf("+----+--------------------------------+--------+\n");
        commandLine(array, line);
        line++;
    }
}
