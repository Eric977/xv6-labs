#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char* argv[]){
    int n = atoi(argv[1]);
    if (argc != 2){
        fprintf(2, "usage: sleep # of ticks\n");
    }
    sleep(n);

    exit(0);
}