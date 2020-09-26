#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "need 1 argumet");
        return 1;
    }

    char *p = argv[1];

    printf(".intel_syntax noprefix\n");
    printf(".globl _main\n");
    printf("_main:\n");
    printf("    mov rax, %d\n", strtol(p, &p, 10));

    while (*p != '\0') {
        if (*p == '+') {
            p++;
            printf("    add rax, %d\n", strtol(p, &p, 10));
        }

        if (*p == '-') {
            p++;
            printf("    sub rax, %d\n", strtol(p, &p, 10));
        }
    }

    printf("    ret\n");

    return 0;
}