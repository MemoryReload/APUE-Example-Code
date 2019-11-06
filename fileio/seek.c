#import "apue.h"
#include <errno.h>

int main (){
    if (lseek(STDIN_FILENO,0,SEEK_CUR) == -1){
        //If the file descriptor refers to a pipe, FIFO, or socket, lseek sets errno to ESPIPE and returns −1
        printf("Error:%d",errno);
        perror(__FILE__);
    } else{
        printf("seek OK!\n");
    }
    exit(0);
}
