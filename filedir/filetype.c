#include "apue.h"

int main(int argc, char *arv[]) {
    struct stat buf;
    char *ptr = NULL;
    for (int i = 1; i < argc ; ++i) {
        printf("%s: ",arv[i]);
        if (lstat(arv[i],&buf)<0){
            err_ret("lstat error");
            continue;
        }
        if(S_ISREG(buf.st_mode)){
            ptr = "regular";
        }else if (S_ISDIR(buf.st_mode)){
            ptr = "directory";
        }else if (S_ISBLK(buf.st_mode)){
            ptr = "block special";
        } else if (S_ISCHR(buf.st_mode)){
            ptr = "character special";
        } else if (S_ISFIFO(buf.st_mode)){
            ptr = "FIFO(Pipe)";
        } else if (S_ISLNK(buf.st_mode)){
            ptr = "symbolic link";
        }else if (S_ISSOCK(buf.st_mode)){
            ptr = "socket";
        } else{
            ptr = "** unkown mode **";
        }
        printf("%s\n",ptr);
    }
    return 0;
}