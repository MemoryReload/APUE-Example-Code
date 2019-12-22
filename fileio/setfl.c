//
// Created by 何平 on 2019/11/8.
//

#include "apue.h"
#include "fcntl.h"

int set_flg (int fd, int flags)
{
    int val;
    //fetch back original flags
    if ((val = fcntl(fd,F_GETFL,0))<0)
    {
        err_msg("fcntl F_GETFL error");
        return -1;
    }
    //add your additional new flag
    val |=flags;
    //set it back 
    if (fcntl(fd,F_SETFL,val) <0)
    {
        err_msg("fcntl F_SETFL error");
        return -1;
    }
    return val;
}
