#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void xargs_helper(char* in_cmd, char* in_arg)
{	
	char args[32][50];
	char* exec_arg[4];
	exec_arg[0] = in_cmd;
	exec_arg[1] = in_arg;
	exec_arg[2] = (char*) malloc(50);
	exec_arg[3] = 0;
	//the exec_arg array is the second input array of exec function, first element is first arguement, second is second
	int i = 0, j = 0;
	while(read(0, &args[i][j], 1)){
		if(args[i][j] == '\n'){
			args[i][j] = 0;
			i++;
			j = 0;
		}
		else j++;
	}//now the args contains i rows of  arguments, all in string form.
	
	

	
	
	for(int j = 0; j < i; j++){
		strcpy(exec_arg[2], args[j]+1);//why+1? in order to avoid the dot which is on the first place of each arg [DOT BUG]

		if (fork() == 0){
			exec(in_cmd, exec_arg);
			printf("exec failed\n");
		}
		else{
			wait(0);
		}
	}

}


int main(int argc, char **argv) {
	char in_cmd[512], in_arg[512];
	memmove(in_cmd, argv[1], strlen(argv[1])+1);
	memmove(in_arg, argv[2], strlen(argv[2])+1);

	xargs_helper(in_cmd,in_arg);


	exit(0);
}
