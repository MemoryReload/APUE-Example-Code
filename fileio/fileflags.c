//
// Created by 何平 on 2019/11/4.
//
#include "apue.h"
#include "fcntl.h"

int main(int args, char* argv[])
{
    if (args != 2)
        err_quit("\"usage: fileflags <descriptor#>\"");
    int val;
    if ((val = fcntl(atoi(argv[1]),F_GETFL,0)) <0)
        err_sys("fcntl error for fd %d", atoi(argv[1]));
    switch (val){
        case O_RDONLY:
            printf("read only");
            break;
        case O_WRONLY:
            printf("write only");
            break;
        case O_RDWR:
            printf("read and write");
            break;
        default:
            printf("unknown access mode");
    }
    if (val && O_APPEND)
        printf(",append");
    if (val && O_NONBLOCK)
        printf(",nonblocking");
    if (val && O_SYNC)
        printf(",synchronous writes");
#if !defined(_POSIX_C_SOURCE) && defined(O_FSYNC) && O_FSYNC != O_SYNC
    if (val && O_FSYNC)
        printf(",synchronous writes");
#endif
    putchar('\n');
    exit(0);
}

