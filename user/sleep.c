#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(2, "Usage: sleep <ticks>\n");  
        exit(1);
    }
    int time = atoi(argv[1]);  //acquire the sleep time from shell cmd
    sleep(time); //invoke system call sleep
    exit(0);
}
