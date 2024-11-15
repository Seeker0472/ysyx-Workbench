#include <stdio.h>

int main(int argc, char *argv[], char *envp[]) {
    printf("%x,%x\n",*argv,*envp);
    printf("argv:\n");
    for (int i = 0; i < argc; i++) {
        printf("argv[%d]: %s\n", i, argv[i]);
    }

    printf("\nenvp:\n");
    if(*envp!=NULL)
        for (char **env = envp; *env != 0; env++) {
          printf("%d\n",*env);
            printf("%s\n", *env);
        }

    return 0;
}

