#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern char ** environ;

int execvpe(char* file, char* argv[], char* envp){
    char** oldEnv = environ;
    if (putenv(envp) == -1){
        perror("ERROR: can`t change env!");
        return -1;
    }
    int res = execvp(file, argv);
    environ = oldEnv;
    return res;
}

int main(int argc, char** argv){
    if (argc < 2){
        perror("ERROR: not enough args!");
        exit(EXIT_FAILURE);
    }
    char *envp = "LINES=30";
    if (execvpe(argv[1], &argv[1], envp) == -1){
        perror("ERROR: failde to execvpe!");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}