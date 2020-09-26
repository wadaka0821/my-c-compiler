#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

typedef enum {
    DIGIT,
    SYMBOL,
    TK_EOF,
} TK;

typedef struct TOKEN TOKEN;

struct TOKEN {
    TK type;
    TOKEN *next;
    int value;
    char str;
};

void add(TOKEN *token, TK type, int val, char str)
{
    while (token->type != TK_EOF) {
        token = token->next;
    }

    TOKEN *new_token = (TOKEN *)malloc(sizeof(TOKEN));
    token->type = type;
    token->next = new_token;
    token->value = val;
    token->str = str;

    new_token->type = TK_EOF;
    new_token->next = NULL;
    new_token->value = -1;
    new_token->str = '\0';
}

void tokenize(TOKEN *head, char *str)
{
    while (*str != '\0') {
        if (*str == ' ') {
            str++;
        } if (*str == '+') {
            add(head, SYMBOL, -1, '+');
            str++;
        } else if (*str == '-') {
            add(head, SYMBOL, -1, '-');
            str++;
        } else if (isdigit(*str)) {
            add(head, DIGIT, strtol(str, &str, 10), '\0');
        }
    }
}

TOKEN * write(TOKEN *token)
{
    if (token->type == TK_EOF) {
        return NULL;
    } else if (token->type == SYMBOL) {
        if (token->str == '+') {
            printf("    add rax, ");
        } else if (token->str == '-') {
            printf("    sub rax, ");
        }
    } else if (token->type == DIGIT) {
        printf("%d\n", token->value);
    }

    TOKEN *tmp = token;
    token = token->next;

    free(tmp);
    return token;
}

void writes(TOKEN *head)
{
    printf("    mov rax, %d\n", head->value);
    TOKEN *tmp = head;
    head = head->next;
    free(tmp);

    while (head->type != TK_EOF) { 
        head = write(head);
    }
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "need 1 argumet");
        return 1;
    }

    char *p = argv[1];

    TOKEN *head = (TOKEN *)malloc(sizeof(TOKEN));
    head->type = TK_EOF;
    tokenize(head, p);

    printf(".intel_syntax noprefix\n");
    printf(".globl _main\n");
    printf("_main:\n");

    writes(head);

    printf("    ret\n");

    return 0;
}