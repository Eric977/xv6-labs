#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


void primes(int fd){
    int n, num;
    int flag = 0;
    read(fd, &n, sizeof(n));
    int pipefd[2];
    printf("prime %d\n", n);
    while (read(fd, &num, sizeof(num)) != 0){
        if (num % n != 0){
            if (!flag){
                pipe(pipefd);
                int pid = fork();
                if (pid == 0){
                    close(pipefd[1]);
                    primes(pipefd[0]);
                }
                else if (pid > 0){
                    close(pipefd[0]);
                    flag = 1;
                }
            }
            write(pipefd[1], &num, sizeof(num));
        }
    }
    close(pipefd[1]);
    if (flag)
        wait(0);
    return;
    
}
int main(int argc, char* argv[]){
    int pipefd[2];
    pipe(pipefd);
    
    int pid = fork();
    if (pid == 0){
        close(pipefd[1]);
        primes(pipefd[0]);
    }
    else{
        close(pipefd[0]);
        for (int i = 2; i <= 35; i ++){
            write(pipefd[1], &i, sizeof(i));
        }
        close(pipefd[1]);
        wait(0);

    }
    exit(0);
}