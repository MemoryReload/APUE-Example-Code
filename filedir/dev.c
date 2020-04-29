//
// Created by 何平 on 2020/4/29.
//
#include "apue.h"

#undef  _SYS_TYPES_H_
#define _DARWIN_C_SOURCE
#include <sys/types.h>

#ifdef SOLARIS
#include <sys/mkdev.h>
#endif


int main (int argc, char *argv[])
{
    if (argc<2)
        err_quit("usage: command filepath");
    for (int i=1; i<argc; i++){
        struct stat  statBuf;
        printf("file: %s",argv[i]);
        if (lstat(argv[i],&statBuf)<0)
        {
            err_msg("cannot stat\n");
            continue;
        }
        printf("\tdev = %ld/%ld",major(statBuf.st_dev),minor(statBuf.st_dev));
        if (S_ISCHR(statBuf.st_mode) || S_ISBLK(statBuf.st_mode)){
            printf("\t(%s) rdev = %d/%d",S_ISCHR(statBuf.st_mode)?"character":"block",major(statBuf.st_rdev),minor(statBuf.st_rdev));
        }
        printf("\n");
    }
}