//
// Created by 何平 on 2020/4/21.
//
#include "apue.h"
#include <fcntl.h>

#define RWRWRW (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)
#define RWXRWXRWX (S_IRWXU | S_IRWXG | S_IRWXO)

int main(int argc, char *argv[])
{

    mode_t originalMask = umask(0);
    printf("original mask: %#o",originalMask);
    //fopen( ) default privilege is -rw-rw-rw and umask will take effect.
    if (fopen("boo","ab+") == NULL){
        err_sys("create error for boo");
    }
    if (creat("foo",RWRWRW)<0){
        err_sys("creat error for foo");
    }
    umask(S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    if (creat("doo",RWRWRW)<0){
        err_sys("create error for bar");
    }
    if (creat("loo",RWXRWXRWX)<0) {
        err_sys("create error for loo");
    }
    return 0;
}