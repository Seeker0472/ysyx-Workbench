#include <stdio.h>

int main(int argc, char *argv[], char *envp[]) {
    printf("%d,%x,%x\n",argc,*argv,*envp);
    printf("argv:\n");
    for (int i = 0; i < argc; i++) {
        printf("argv[%d]: %s\n", i, argv[i]);
    }

    printf("\nenvp:\n");
    for (char **env = envp; *env != 0; env++) {
        printf("%s\n", *env);
    }
    printf("\nEOF\n");

    return 0;
}

