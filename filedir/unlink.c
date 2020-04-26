//
// Created by 何平 on 2020/4/26.
//
#include "apue.h"
#include <fcntl.h>

int main (int argc, char *argv[])
{
    if (argc !=2) {
        err_quit("usage: command path");
    }
    if (open(argv[1],O_CREAT | O_RDWR)<0){
        err_sys("failed to open file: %s",argv[1]);
    }
    if (unlink(argv[1])<0){
        err_sys("failed to unlink file: %s",argv[1]);
    }
    printf("file unlinked!\n");
    sleep(15);
    printf("done!\n");
    exit(0);
}