#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char* argv[]){
    int fd[2], fd2[2];
    pipe(fd);       // child to parent
    pipe(fd2);      // Parent to child
    
    char *msg = "a";
    int pid = fork();
    if (pid == 0){
        char *buf[40];

        close(fd[0]);
        close(fd2[1]);

        read(fd2[0], buf, sizeof(buf));
        fprintf(1, "%d: received ping\n", getpid());
        write(fd[1], msg, sizeof(msg));


    }
    else if (pid > 0){
        char* buf[20];

        close(fd[1]);
        close(fd2[0]);

        write(fd2[1], msg, sizeof(msg));
        read(fd[0], buf, sizeof(buf));
        fprintf(1, "%d: received pong\n", getpid());


    }
    else{
        printf("fork error");
    }
    exit(0);
}