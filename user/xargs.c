#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/param.h"
#include "user/user.h"
#define MAX 20
void xargs(char *path, char **argv){
    int pid = fork();
    if (pid == 0){
        exec(path, argv);
    }
    else if (pid > 0){
        wait(0);
    }
    return;
    
}
int main(int argc, char* argv[]){
    //printf("%s\n", argv[1]);
    char buf[MAXARG];
    char *p[MAXARG];
    
    for (int i = 1; i < argc; i ++){
        p[i - 1] = argv[i];
    }
    
    p[argc - 1] = buf;
    int i = 0;
    while(read(0, &buf[i++], 1)){
        if (buf[i - 1] == '\n'){
            buf[i - 1] = '\0';
            xargs(argv[1], p);
            i = 0;
        }
    }
    exit(0);
}