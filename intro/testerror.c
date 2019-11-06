#include "apue.h"
#include <errno.h>

int main (int argc, char *argv[]){
    //打印到标准错误流，strerror把错误码转换成描述
    fprintf(stderr,"EACCES: %s\n",strerror(EACCES));
    errno = ENOENT;
    //打印出错原因，参数为前导字符串。
    perror(argv[0]);
    exit(0);
}