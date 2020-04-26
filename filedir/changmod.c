//
// Created by 何平 on 2020/4/24.
//
#include "apue.h"
#include <fcntl.h>

#define RWRWRW (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)
#define RWXRWXRWX (S_IRWXU | S_IRWXG | S_IRWXO)

int main (int argc, char *argv[])
{
    struct stat statBuf;
    if (stat("foo",&statBuf)<0) {
        err_sys("stat error for foo");
    };
    if (chmod("foo",(statBuf.st_mode & ~S_IXGRP) | S_ISGID)<0){
        err_sys("create error for foo");
    }
    /* set absolute mode to "rw-r--r--" */
    if (chmod("doo", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) < 0) {
        err_sys("chmod error for doo");
    }
    return 0;
}