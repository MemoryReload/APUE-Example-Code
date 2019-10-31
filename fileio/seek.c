#import "apue.h"

int main (){
    if (lseek(STDIN_FILENO,0,SEEK_CUR) == -1){
        //If the file descriptor refers to a pipe, FIFO, or socket, lseek sets errno to ESPIPE and returns −1
        printf("cannot seek!\n");
    } else{
        printf("seek OK!\n");
    }
    exit(0);
}
