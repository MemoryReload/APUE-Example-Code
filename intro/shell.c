#include "apue.h"

static void sig_int(int);//signal-catching function

int main() {

    printf("Process ID: %ld\n",(long)getpid());

    char buf[MAXLINE];
    pid_t pid;
    int status;

    if (signal(SIGINT, sig_int) == SIG_ERR)
        err_sys("signal error");

    printf("%% ");

    while (fgets(buf,MAXLINE,stdin) !=  NULL){
        if (buf[strlen(buf)-1] == '\n')
            buf[strlen(buf)-1] = '\0';
        if ((pid = fork()) < 0){
            err_sys("fork error");
        } else if (pid == 0){
            execlp(buf,buf,NULL);
            err_ret("couldn't execute: %s", buf);
            _exit(127);
        }
        if ((pid = waitpid(pid,&status,0)) <0)
            err_sys("waitpid error");
        printf("%% ");
    }
    return 0;
}

void sig_int(int signo){
    printf("interrupt\n%%");
}