#include "apue.h"
#include <dirent.h>

int main(int argc, char* args[]) {
    if (argc != 2)
        err_quit("usage: ls directory_name");
    DIR* dir = opendir(args[1]);
    if (dir == NULL)
        err_sys("can't open %s", args[1]);
    struct dirent * entry =  readdir(dir);
    while (entry != NULL){
        printf("%s\n", entry->d_name);
        entry = readdir(dir);
    }
    closedir(dir);
    exit(0);
}