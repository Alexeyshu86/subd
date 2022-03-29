#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main() {
    char str1[10];
    char str2[6] = "Hello";
    int len;

    fgets(str1, 10, stdin);
    len = strlen(str1);
    str1[len - 1] = '\0';

    if (strcmp(str1, str2) == 0) {
        printf("OK\n");
    } else {
        printf("no OK\n");
    }

    return 0;
}