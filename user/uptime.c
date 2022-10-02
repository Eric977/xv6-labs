#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char* argv[]){
    if (argc > 1){
        fprintf(2, "too many argument\n");
        exit(0);
    }
    int ut = uptime();
    printf("up %d ticks\n", ut);
    exit(0);
}
