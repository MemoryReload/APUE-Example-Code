//
// Created by 何平 on 2020/4/26.
//
#include "apue.h"
#include <fcntl.h>
#include <time.h>

int main (int argc, char *argv[]){
    if (argc<2){
        err_quit("usage: command path ...");
    }
    struct stat staBuf;
    struct timespec times[2];
    int fd = 0;
    for (int i=1; i<argc; i++){
        if (stat(argv[1],&staBuf)<0){
            err_msg("failed to fetch stat with file: %s",argv[i]);
            continue;
        }
        if ((fd = open(argv[1], O_WRONLY | O_TRUNC))<0){
            err_msg("failed to open file: %s",argv[i]);
            continue;
        }
#if !defined(_POSIX_C_SOURCE) || defined(_DARWIN_C_SOURCE)
        times[0] =  staBuf.st_atimespec;
        times[1] =  staBuf.st_mtimespec;
#else
        times[0].tv_sec = staBuf.st_atime;
        times[0].tv_nsec = staBuf.st_atimensec;
        times[1].tv_sec = staBuf.st_mtime;
        times[1].tv_nsec = staBuf.st_mtimensec;
#endif
        if (futimens(fd,times)<0){
            err_msg("failed to set time with file: %s",argv[i]);
            continue;
        }
    }
    return 0;
}