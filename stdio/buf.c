#include "apue.h"
#include <stdio.h>

int pr_stdio(char* filename, FILE* file);
int is_linebuffered(FILE* file);
int is_fullbuffered(FILE* file);
int buffer_size(FILE* file);

int main() {
    fputs("enter any character\n",stdout);
    if (getchar() == EOF)
        err_sys("getchar error");
    fputs("one line to standard error\n",stderr);

    pr_stdio("stdin",stdin);
    pr_stdio("stdout",stdout);
    pr_stdio("stderr",stderr);
}
