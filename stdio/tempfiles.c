//
// Created by 何平 on 2020/6/9.
//
#include "apue.h"
#include <stdio.h>

int main (int argc, char * argv[]){
    char tmp_path[L_tmpnam] = "";
    FILE * file = NULL;
    char buffer[MAXLINE] = "";

    printf("%s\n",tmpnam(NULL));
    tmpnam(tmp_path);
    printf("%s\n",tmp_path);

    if (NULL == (file = tmpfile()))
        err_sys("tmpfile error");
    fputs("one line of output\n",file);
    rewind(file);
    if (fgets(buffer,MAXLINE,file) == NULL)
        err_sys("fgets error");
    fputs(buffer,stdout);
}