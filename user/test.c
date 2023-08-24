#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int main(int argc, char **argv) {

//	for(int j = 0; j < i; j++){
//		strcpy(exec_arg[1], args[j]);
		char* a[3] = {"echo","dddd2"};
		char* s = "echo";
		if (fork() == 0){
			exec(s,a);
			printf("exec failed\n");
		}
		else{
			wait(0);
		}
//	}



	exit(0);
}
