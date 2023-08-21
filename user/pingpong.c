#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
int
main(int argc, char *argv[])
{
  int p2c[2],c2p[2];//used for holding fd of the pipe "parent to child(p2c)" and the pipe "child to parent(c2p)";
  char buff[] = {'g'};
  if(pipe(p2c) == -1){
  	fprintf(2, "error by creating pipe parent to child.");
	exit(1);
  }
  if(pipe(c2p) == -1){
 	fprintf(2, "error by creating pipe child to parent.");
	exit(1);
  }
  
  int pid_value = fork();
  if (pid_value < 0){
  	fprintf(2, "error by forking.");
	exit(1);
  }
  else if(pid_value == 0){//child process
  	close(p2c[1]);
	close(c2p[0]);

	if(read(p2c[0],buff,1) == 1){
		printf("%d: received ping\n",getpid());
		write(c2p[1],buff,1);
	}
	else{
		fprintf(2, "receiving error.");
		exit(1);
	}
	exit(0);
  }
  else{//parent process
  	close(p2c[0]);
	close(c2p[1]);

	write(p2c[1], buff,1);

	if(read(c2p[0],buff,1) == 1){
		printf("%d: received pong\n", getpid());
	}
	else{
		fprintf(2, "receiving error parent.");
		exit(1);
	}
	exit(0);
  }
}
